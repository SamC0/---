/*
 * KalmanFilter.h
 * Non-original
 * Author: x2d 
 * Copyright (c) 2012 China
 *
 */

#ifndef KalmanFilter_h
#define KalmanFilter_h

//#include <WProgram.h>
//
//class KalmanFilter
//{
//  KalmanFilter();
//  /*
//    卡尔曼融合计算
//    angle_m: 加速度计测量并通过atan2(ax,ay)方法计算得到的角度（弧度值）
//    gyro_m:陀螺仪测量的角速度值（弧度值）
//    dt:采样时间(s)
//    outAngle:卡尔曼融合计算出的角度（弧度值）
//    outAngleDot:卡尔曼融合计算出的角速度（弧度值）
//  */
//  void getValue(double angle_m, double gyro_m, double dt, double &outAngle, double &outAngleDot);
//  
//  double C_0, Q_angle, Q_gyro, R_angle;
//  double q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//  double angle, angle_dot;
//  double P[2][2];
//  double Pdot[4];
//};
//
//#include "sys.h"
//
//#define Q_angle 0.01      // 角度数据置信度
//#define Q_omega 0.0003    // 角速度数据置信度
//#define R_angle 0.01      // 方差噪声
//
//extern u8 filted_mode;
//
//float First_order_filter(float Com_angle,float angle_pt,float angle,float dt);// 一阶互补算法
//float Second_order_filter(float Com2_angle,float angle_pt,float angle,float dt);// 二阶互补算法
//float Kalman_filter(float Klm_angle,float angle_pt,float angle,float dt);// 卡尔曼滤波
//


  #endif
//end of file
