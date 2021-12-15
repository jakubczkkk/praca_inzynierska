#pragma once

struct Quaternion {

    double q0, q1, q2, q3;

    Quaternion(double a = 0, double b = 0, double c = 0, double d = 0) : q0(a), q1(b), q2(c), q3(d) { }

    Quaternion operator*(Quaternion q) {
        Quaternion r;
        r.q0 = q0 * q.q0 - q1 * q.q1 - q2 *  q.q2 - q3 * q.q3;
        r.q1 = q1 * q.q0 + q0 * q.q1 - q3 *  q.q2 + q2 * q.q3;
        r.q2 = q2 * q.q0 + q3 * q.q1 + q0 *  q.q2 - q1 * q.q3;
        r.q3 = q3 * q.q0 - q2 * q.q1 + q1 *  q.q2 + q0 * q.q3;
        return r;
    }

};
