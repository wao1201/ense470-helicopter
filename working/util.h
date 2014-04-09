//  -*- c++ -*-
#ifndef UTIL_H
#define UTIL_H

/**
    Utility classes and constants related to mechanics.
*/


struct Orientation {

public:
    Orientation(float x_theta=0, float y_theta=0, float z_theta=0) :
        x_theta(x_theta), y_theta(y_theta), z_theta(z_theta) {}

    float x_theta;
	float y_theta;
    float z_theta;
};


// struct AngularSpeed {
    
// public:
//     AngularSpeed(float wx=0, float wy=0, float wz=0) :
// 		wx(wx), wy(wy), wz(wz) {}

// 	void set(float wx, float vy, float vz) {
//         this->wx = wx; this->wy = wy; this->wz = wz;
// 	}
// 	float wx;
// 	float wy;
// 	float wz;
// };



#endif // UTIL_H
