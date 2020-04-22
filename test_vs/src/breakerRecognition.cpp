#include "breakerRecognition.h"
breakerRecognition::breakerRecognition(){
        imagePath = "./image_get.jpg";
        modelPath = "./model.jpg";
        contourMatchPath = "./contourMatch.jpg";
}
bool breakerRecognition::getSrcImage(){
    VideoCapture capture("../video/2.mp4");
    if (!capture.isOpened())
    {
        cout << "设备未连接,请检查设备连接状态！" << endl;
        return false;
    }

    for (int i = 0; i <= 100;i++){
        capture >> srcImage;
        if (i == 100) {
            // 检查是否读取图像
            if (srcImage.empty()) {
                    cout << "未抓取到图片！" << endl;
                    return false;
            }
            imwrite(imagePath, srcImage);
         }
    }
    return true;
}

bool breakerRecognition::getModelImage() {
        if (setsrcImage()) {
                modelImage = imageClip(srcImage).clone();
                imwrite(modelPath, modelImage);
                return true;
        }
        else
        {
                return false;
        }
}

bool breakerRecognition::setsrcImage(){
        srcImage = imread(imagePath, IMREAD_COLOR);
        // 检查是否读取图像
        if (srcImage.empty()) {
                cout << "请抓取图片！" << endl;
                return false;
        }
        return true;
}

bool breakerRecognition::setModelImage() {
        modelImage = imread(modelPath, IMREAD_COLOR);
        // 检查是否读取图像
        if (modelImage.empty()) {
                cout << "请截取模板！" << endl;
                return false;
        }
        return true;
}

vector<vector<Point>> breakerRecognition::getContour(Mat image) {
        //1.图像预处理
        //1.1阈值化
        cvtColor(image, image, COLOR_BGR2GRAY);					//灰度图（阈值化需要灰度图）
        threshold(image, image, 80, 255, THRESH_BINARY_INV);	//阈值化:黑色背景白色轮廓

        //1.2canny边缘检测
        /*
        blur(srcImage, srcImage, Size(7, 7));
        cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
        Canny(srcImage, srcImage, 10, 100, 3, false);
        */

        //2.查找轮廓并绘制轮廓
        vector<vector<Point>> contours;		//轮廓

        //2.1查找轮廓——findContours()

        //轮廓检索模式：RETR_EXTERNAL（检测最外层）
        //轮廓检索模式：RETR_TREE及其他（检测所有轮廓）

        //轮廓近似方法：CHAIN_APPROX_NONE（存储所有的轮廓点）
        //轮廓近似方法：CHAIN_APPROX_SIMPLE（只存储端点）
        findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        return contours;
}

Mat breakerRecognition::imageClip(Mat image) {
        Rect rect(280, 150, 100, 100);
        return image(rect);
}

void breakerRecognition::histogramIntensification() {
        imshow("原图像", srcImage);
        Mat imageRGB[3];
        split(srcImage, imageRGB);
        for (int i = 0; i < 3; i++)
        {
                equalizeHist(imageRGB[i], imageRGB[i]);
        }
        merge(imageRGB, 3, srcImage);
}

void breakerRecognition::laprasIntensification(Mat image) {
        imshow("原图像", image);
        Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 3, 0, 0, -1, 0);
        filter2D(image, image, CV_8UC3, kernel);
}

void breakerRecognition::logIntensification() {
        Mat imageLog(srcImage.size(), CV_32FC3);
        for (int i = 0; i < srcImage.rows; i++)
        {
                for (int j = 0; j < srcImage.cols; j++)
                {
                        imageLog.at<Vec3f>(i, j)[0] = log(1 + srcImage.at<Vec3b>(i, j)[0]);
                        imageLog.at<Vec3f>(i, j)[1] = log(1 + srcImage.at<Vec3b>(i, j)[1]);
                        imageLog.at<Vec3f>(i, j)[2] = log(1 + srcImage.at<Vec3b>(i, j)[2]);
                }
        }
        //归一化到0~255
        normalize(imageLog, imageLog, 0, 255, NORM_MINMAX);
        //转换成8bit图像显示
        convertScaleAbs(imageLog, imageLog);
        srcImage = imageLog.clone();
}

void breakerRecognition::gammaIntensification() {
        Mat imageGamma(srcImage.size(), CV_32FC3);
        for (int i = 0; i < srcImage.rows; i++)
        {
                for (int j = 0; j < srcImage.cols; j++)
                {
                        imageGamma.at<Vec3f>(i, j)[0] = (srcImage.at<Vec3b>(i, j)[0]) * (srcImage.at<Vec3b>(i, j)[0]) * (srcImage.at<Vec3b>(i, j)[0]);
                        imageGamma.at<Vec3f>(i, j)[1] = (srcImage.at<Vec3b>(i, j)[1]) * (srcImage.at<Vec3b>(i, j)[1]) * (srcImage.at<Vec3b>(i, j)[1]);
                        imageGamma.at<Vec3f>(i, j)[2] = (srcImage.at<Vec3b>(i, j)[2]) * (srcImage.at<Vec3b>(i, j)[2]) * (srcImage.at<Vec3b>(i, j)[2]);
                }
        }
        //归一化到0~255
        normalize(imageGamma, imageGamma, 0, 255, NORM_MINMAX);
        //转换成8bit图像显示
        convertScaleAbs(imageGamma, imageGamma);
        srcImage = imageGamma.clone();
}

//功能函数：
//1. 颜色识别
bool breakerRecognition::colorRecognition() {
        int threshold = 500;	// 像素阈值
        cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);	// 转化为HSV格式

        //用来记录图像中白色像素的数目，初始化为图像像素总数，
        int pixel_size = hsvImage.rows * hsvImage.cols;
        for (int i = 0; i < hsvImage.rows; ++i)
        {
                for (int j = 0; j < hsvImage.cols; ++j)
                {
                        //hsvImage.at<Vec3b>(i, j):获取像素点为（j, i）点的HSV的值,根据白色像素HSV值进行分割
                        if (!((hsvImage.at<Vec3b>(i, j)[1] > 70 && hsvImage.at<Vec3b>(i, j)[1] < 100)
                                && (hsvImage.at<Vec3b>(i, j)[2] > 150 && hsvImage.at<Vec3b>(i, j)[2] < 220)))
                        {
                                hsvImage.at<Vec3b>(i, j)[0] = 0;
                                hsvImage.at<Vec3b>(i, j)[1] = 0;
                                hsvImage.at<Vec3b>(i, j)[2] = 0;
                                --pixel_size;
                        }
                }
        }

        // 写入分割后的图片
        cvtColor(hsvImage, aftRecognition, COLOR_BGR2HSV);
        imwrite("aft_segmentation.jpg", aftRecognition);

        // 显示分割前、后图片
        imshow("bef_segmentation", srcImage);
        imshow("aft_segmentation", aftRecognition);

        cout << "白色像素数：" << pixel_size << endl;
        if (pixel_size < threshold) {
                cout << "按下状态" << endl;
                return true;
        }
        else {
                cout << "拔出状态" << endl;
                return false;
        }
        waitKey(0);
}

//2. 轮廓匹配
bool breakerRecognition::contourMatch() {
        getModelImage();
    //1.查找模版图像的轮廓
    if (setModelImage()) {
        //laprasIntensification(modelImage);
        modelContour = getContour(modelImage);
        //drawContours(modelImage, modelContour, -1, Scalar(0, 255, 0), 2, 8);
        //imshow("modelContour", modelImage);
    }

    //2.查找待测试图像的轮廓,and match
    if (getSrcImage()) {
        //laprasIntensification(srcImage);
        aftRecognition = imageClip(srcImage).clone();   //clip image
        imageContours = getContour(aftRecognition);
        //imshow("srcImage", srcImage);
        for (size_t i = 0; i < imageContours.size(); i++) {     //遍历待识别图像轮廓
            for (size_t j = 0; j < modelContour.size(); j++) {      //遍历模板轮廓
                //轮廓相似度,similarity越小越相似
                double similarity = matchShapes(imageContours[i],modelContour[j],CV_CONTOURS_MATCH_I1, 0);
                cout << "模版轮廓与待测试图像轮廓" << i << "的相似度:" << similarity << endl;   //输出相似度
                if (similarity < 0.1) {     //threshold
                    drawContours(aftRecognition, imageContours, i, Scalar(0, 255, 0), 2, 8);    //write轮廓
                //     dj::breakerState = 1;   // pull,initialized push
                    //cout << "拔出状态" << endl;
                }
            }
        }
        imwrite(contourMatchPath, aftRecognition);
        //cout << "按下状态" << endl;
    }
    return true;
}

//3. 轮廓选取
bool breakerRecognition::contourSelect() {
        if (setsrcImage()) {									//获取图像，并写入Mat
                //laprasIntensification(srcImage);
                aftRecognition = imageClip(srcImage).clone();		//截取断路器图像
                imageContours = getContour(aftRecognition);
                imshow("srcImage", aftRecognition);
                for (size_t i = 0; i < imageContours.size(); i++)		//遍历待识别图像轮廓
                {
                        //根据轮廓面积进行选取
                        if (contourArea(imageContours[i], false) > 400 && contourArea(imageContours[i], false) < 500)
                        {
                                drawContours(aftRecognition, imageContours, i, Scalar(0, 255, 0), 2, 8);//则在待测试图像上画出此轮廓
                                cout << "轮廓面积：" << contourArea(imageContours[i], false) << endl;
                                cout << "按下状态" << endl;
                                waitKey(0);
                                return false;
                        }
                        imshow("aftRecognition", aftRecognition);
                }
                cout << "拔出状态" << endl;
                waitKey(0);
        }
        return true;
}

bool breakerRecognition::showVedio() {
        VideoCapture capture(0);
        Mat image;
        if (!capture.isOpened())
        {
                cout << "设备未连接,请检查设备连接状态！" << endl;
                return false;
        }
        while (true)
        {
                capture >> image;
                namedWindow("showVedio", WINDOW_NORMAL);
                imshow("showVedio", image);
                waitKey(1);
        }
}
