/*
 * KalmanFilter.cpp
 * Non-original
 * Author: x2d 
 * Copyright (c) 2012 China
 *
 */
 
 #include "KalmanFilter.h"
 
// KalmanFilter::KalmanFilter()
// {
//   C_0 = 1.0f;
//   Q_angle = 0.001f;
//   Q_gyro = 0.003f;
//   R_angle = 0.5f;
//   q_bias = angle_err = PCt_0 = PCt_1 = E = K_0 = K_1 = t_0 = t_1 = 0.0f;
//   angle = angle_dot = 0.0f;
//   P[0][0] = 1.0f;
//   P[0][1] = 0.0f;
//   P[1][0] = 0.0f;
//   P[1][1] = 1.0f;
//   Pdot[0] = 0.0f;
//   Pdot[1] = 0.0f;
//   Pdot[2] = 0.0f;
//   Pdot[3] = 0.0f;
// }
// 
//void  KalmanFilter::getValue(double angle_m, double gyro_m, double dt, double &outAngle, double &outAngleDot)
//{
///*
//  Serial.print("angle_m = ");
//  Serial.print(angle_m);
//  Serial.print(";");
//  Serial.print("gyro_m = ");
//  Serial.print(gyro_m);
//  Serial.print(";");
//*/
//
//  angle+=(gyro_m-q_bias) * dt;
//  angle_err = angle_m - angle;
//  Pdot[0] = Q_angle - P[0][1] - P[1][0];
//  Pdot[1] = -P[1][1];
//  Pdot[2] = -P[1][1];
//  Pdot[3] = Q_gyro;
//  P[0][0] += Pdot[0] * dt;
//  P[0][1] += Pdot[1] * dt;
//  P[1][0] += Pdot[2] * dt;
//  P[1][1] += Pdot[3] * dt;
//  PCt_0 = C_0 * P[0][0];
//  PCt_1 = C_0 * P[1][0];
//  E = R_angle + C_0 * PCt_0;
//  K_0 = PCt_0 / E;
//  K_1 = PCt_1 / E;
//  t_0 = PCt_0;
//  t_1 = C_0 * P[0][1];
//  P[0][0] -= K_0 * t_0;
//  P[0][1] -= K_0 * t_1;
//  P[1][0] -= K_1 * t_0;
//  P[1][1] -= K_1 * t_1;
//  angle += K_0 * angle_err;
//  q_bias += K_1 * angle_err;
//  angle_dot = gyro_m-q_bias;
//  
//  outAngle = angle;
//  outAngleDot = angle_dot;
///*
//  Serial.print("angle = ");
//  Serial.print(angle);
//  Serial.print(";");
//  Serial.print("angle_dot = ");
//  Serial.print(angle_dot);
//  Serial.print(";");
//*/
//}
////网上找的另一个
//float Kalman_filter(float Klm_angle,float angle_pt,float angle,float dt)// 卡尔曼滤波
//{
// static float bias;
// static float P_00,P_01,P_10,P_11;
// float K_0,K_1;
//    Klm_angle += (angle_pt - bias) * dt;       // 先验估计
//    P_00 += -(P_10 + P_01) * dt + Q_angle *dt;
//    P_01 += -P_11 * dt;
//    P_10 += -P_11 * dt;
//    P_11 += +Q_omega * dt;                     // 先验估计误差协方差
//     
//    K_0 = P_00 / (P_00 + R_angle);
//    K_1 = P_10 / (P_00 + R_angle);
//     
//    bias += K_1 * (angle - Klm_angle);
//    Klm_angle += K_0 * (angle - Klm_angle);    // 后验估计
//    P_00 -= K_0 * P_00;
//    P_01 -= K_0 * P_01;
//    P_10 -= K_1 * P_00;
//    P_11 -= K_1 * P_01;                        // 后验估计误差协方差
// return Klm_angle;
//}
//u8 filted_mode=1;
//
//float First_order_filter(float Com_angle,float angle_pt,float angle,float dt)// 一阶互补算法
//{
//    float A,K = 0.075;                             // 对加速度计取值的权重
//    A = K / (K + dt);
//    Com_angle = A * (Com_angle + angle_pt * dt) + (1-A) * angle;
//	return Com_angle;
//}
//
//float Second_order_filter(float Com2_angle,float angle_pt,float angle,float dt)// 二阶互补算法
//{   
//    float x1,x2,K = 0.5;
//	static float y1;
//    x1 = (angle - Com2_angle) * K * K;
//    y1 = y1 + x1 * dt;
//    x2 = y1 + 2 * K *(angle - Com2_angle) + angle_pt;
//    Com2_angle = Com2_angle + x2 * dt;
//	return Com2_angle;
//}
//
//float Kalman_filter(float Klm_angle,float angle_pt,float angle,float dt)// 卡尔曼滤波
//{
//	static float bias;
//	static float P_00,P_01,P_10,P_11;
//	float K_0,K_1;
//    Klm_angle += (angle_pt - bias) * dt;       // 先验估计
//    P_00 += -(P_10 + P_01) * dt + Q_angle *dt;
//    P_01 += -P_11 * dt;
//    P_10 += -P_11 * dt;
//    P_11 += +Q_omega * dt;                     // 先验估计误差协方差
//    
//    K_0 = P_00 / (P_00 + R_angle);
//    K_1 = P_10 / (P_00 + R_angle);
//    
//    bias += K_1 * (angle - Klm_angle);
//    Klm_angle += K_0 * (angle - Klm_angle);    // 后验估计
//    P_00 -= K_0 * P_00;
//    P_01 -= K_0 * P_01;
//    P_10 -= K_1 * P_00;
//    P_11 -= K_1 * P_01;                        // 后验估计误差协方差
//	return Klm_angle;
//}


//end of file
