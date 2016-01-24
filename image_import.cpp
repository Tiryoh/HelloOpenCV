#include <opencv2/opencv.hpp>


int
main (int argc, char **argv)
{
  IplImage *img = 0;
  int interrupt_key;
  // 画像読み込み
  // （引数が少ない場合と無効なデータの場合はエラーを返して終了）
  if ((argc < 2) || ((img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR)) == NULL))
  {
    printf("ERROR!\n");
    return -1;
  }

  // 画像表示
  while (interrupt_key != 'q' && interrupt_key != '\x1b') {
    cvNamedWindow ("image", CV_WINDOW_AUTOSIZE);
    cvShowImage ("image", img);
  
    interrupt_key = cvWaitKey (0);
  }
  
  // 終了
  cvDestroyWindow ("image");
  cvReleaseImage (&img);

  return 0;
}

