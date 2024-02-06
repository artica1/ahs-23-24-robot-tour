#ifndef ODOMETRY_H
#define ODOMETRY_H

extern float dxmm;
extern float leftdymm;
extern float rightdymm;

extern float alphaL;
extern float alphaR;

extern float arclengthL;
extern float arclengthR;

extern float radiusL;
extern float radiusR;

extern float gamma;

extern float dx;
extern float dy;
extern float dTheta;

// yeah current process
extern float localX;
extern float localY;
extern float localTheta; // Radians

bool convertMouseData();

float calcAlpha(float x, float y);

float calcArcLength(float x, float y, float alpha);

float calcRotation(float dyL, float dyR, float aL, float aR, float lL, float lR, int D);

float calcRadius(float arclength, float dT);

float calcXMovement(float radius, float alpha, float dT, float offset);

float calcYMovement(float radius, float alpha, float dT);

bool calculateDeltas();

bool calculatePosition();

bool resetLocalPos();

#endif