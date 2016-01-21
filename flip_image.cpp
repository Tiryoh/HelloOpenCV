#include <opencv2/opencv.hpp>


int
main (int argc, char **argv)
{
  IplImage *src_img = 0;
  IplImage *dst_img_1, *dst_img_2, *dst_img_3;

  // (1)画像を読み込み，同じサイズの出力画像を用意する
  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;
  dst_img_1 = cvCloneImage (src_img);
  dst_img_2 = cvCloneImage (src_img);
  dst_img_3 = cvCloneImage (src_img);

  // (2)画像の水平軸反転・垂直軸反転・両軸反転を行う
  cvFlip (src_img, dst_img_1, 0);
  cvFlip (src_img, dst_img_2, 1);
  cvFlip (src_img, dst_img_3, -1);

  // (3)結果を表示する
  cvNamedWindow ("src", CV_WINDOW_AUTOSIZE);
  cvNamedWindow ("dst_1", CV_WINDOW_AUTOSIZE);
  cvNamedWindow ("dst_2", CV_WINDOW_AUTOSIZE);
  cvNamedWindow ("dst_3", CV_WINDOW_AUTOSIZE);
  cvShowImage ("src", src_img);
  cvShowImage ("dst_1", dst_img_1);
  cvShowImage ("dst_2", dst_img_2);
  cvShowImage ("dst_3", dst_img_3);
  cvWaitKey (0);

  cvDestroyWindow ("src");
  cvDestroyWindow ("dst_1");
  cvDestroyWindow ("dst_2");
  cvDestroyWindow ("dst_3");
  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img_1);
  cvReleaseImage (&dst_img_2);
  cvReleaseImage (&dst_img_3);

  return 1;
}

