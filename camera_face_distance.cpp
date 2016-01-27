// 
//  face_distance.cpp
//
//  Created by Tiryoh on 1/17/16.
//  Copyright (c) 2016 Tiryoh. All rights reserved.
//
//  This software is released under the MIT License.
//

#include <opencv2/opencv.hpp>
#include <iostream>

int
main (int argc, char **argv)
{
    //変数宣言
    int i,key;
    int radius = 195,refradius = 195;
    double refDistance = 0.30;
    char faceID[50],distance[50],currDiameter[50],refDiameter[50];
    
    
    // ブーストされた分類器のカスケードを読み込む
    const char *cascade_name = "./data/haarcascade_frontalface_default.xml";
    CvHaarClassifierCascade *cascade = 0;
    cascade = (CvHaarClassifierCascade *) cvLoad (cascade_name, 0, 0, 0);
    
    
    // 画像を読み込む
    double height = 240*2,width = 320*2;
    CvCapture *capture = 0;
    IplImage *src_img = 0, *src_gray = 0;
    capture = cvCreateCameraCapture(0);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
    
    // そのほか初期化
    CvMemStorage *storage = 0;
    CvSeq *faces;
    static CvScalar colors[] = {
        {{0, 0, 255}}, {{0, 128, 255}},
        {{0, 255, 255}}, {{0, 255, 0}},
        {{255, 128, 0}}, {{255, 255, 0}},
        {{255, 0, 0}}, {{255, 0, 255}}
    };
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 2.0, 2.0);
    
    
    //loop
    while(key != 'q' && key != '\x1b'){
        src_img = cvQueryFrame(capture);
        src_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
        
        
        // メモリを確保し，読み込んだ画像のグレースケール化，ヒストグラムの均一化を行う
        storage = cvCreateMemStorage (0);
        cvClearMemStorage (storage);
        cvCvtColor (src_img, src_gray, CV_BGR2GRAY);
        cvEqualizeHist (src_gray, src_gray);
        
        // 物体（顔）検出
        faces = cvHaarDetectObjects (src_gray, cascade, storage, 1.11, 2, 0, cvSize (30, 30));
        
        // 検出された全ての顔位置に，円を描画する
        for (i = 0; i < (faces ? faces->total : 0); i++) {
            CvRect *r = (CvRect *) cvGetSeqElem (faces, i);
            CvPoint center;
            center.x = cvRound (r->x + r->width * 0.5);
            center.y = cvRound (r->y + r->height * 0.5);
            radius = cvRound ((r->width + r->height) * 0.25);
            cvCircle (src_img, center, radius, colors[i % 8], 2, 8, 0);
            sprintf(faceID, "No.%d", i + 1);
            cvPutText(src_img, faceID, cvPoint(center.x + radius/4, (center.y - radius)), &font, CV_RGB(255, 255, 0));
            sprintf(distance, "%0.3lfm", refDistance * refradius/radius);
            cvPutText(src_img, distance, cvPoint(center.x + radius/4, (center.y + radius + 5)), &font, CV_RGB(0, 255, 255));
            sprintf(currDiameter, "  current diameter:%d", radius*2);
            cvPutText(src_img, currDiameter, cvPoint(10, 50), &font, CV_RGB(255, 255, 0));
            
            printf("radius:%d,distance:%0.3lfm\n" ,radius,refDistance * refradius/radius);
            
        }
        
        if(key == 'i')refradius=radius;
        sprintf(refDiameter, "reference diameter:%d", refradius*2);
        cvPutText(src_img, refDiameter, cvPoint(10, 25), &font, CV_RGB(255, 255, 0));
        
        // 画像を表示，キー入力を取得
        cvNamedWindow ("Face Detection", CV_WINDOW_AUTOSIZE);
        cvShowImage ("Face Detection", src_img);
        key = cvWaitKey (10);
        
    }
    
    //終了処理
    cvDestroyWindow ("Face Detection");
    cvReleaseImage (&src_img);
    cvReleaseImage (&src_gray);
    cvReleaseMemStorage (&storage);
    
    return 0;
}

