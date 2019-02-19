#ifndef __NVIDIA_LOGO_H__
#define __NVIDIA_LOGO_H__

#include <GL/glut.h>

static void makeNvidiaLogo(void)
{
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-1.06485f, 2.81135f);
    glVertex2f(-1.06478f, 2.05894f);
    glVertex2f(-2.05154f, 1.85121f);
    glVertex2f(-2.83056f, 1.43573f);
    glVertex2f(-3.50570f, 0.96090f);
    glVertex2f(-5.00000f, 5.00000f);
    glVertex2f( 5.00000f, 5.00000f);
    glVertex2f( 3.97311f, 2.81135f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-2.39205f, 0.536978f);
    glVertex2f(-2.36314f, 1.183480f); 
    glVertex2f(-2.04704f, 0.806418f);
    glVertex2f(-1.79187f, 1.495080f);
    glVertex2f(-1.63302f, 1.016710f);
    glVertex2f(-1.06478f, 1.658310f);
    glVertex2f(-1.03500f, 1.167860f); 
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-2.53006f,  0.260968f);
    glVertex2f(-2.41505f, -0.047902f);
    glVertex2f(-2.10347f, -1.220340f);
    glVertex2f(-2.57088f, -0.760353f);
    glVertex2f(-2.83056f, -0.315201f);
    glVertex2f(-2.36314f,  1.183480f);
    glVertex2f(-2.39205f,  0.536978f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -2.83056f,  0.842190f);
    glVertex2f( -2.36314f,  1.183480f);
    glVertex2f( -2.83056f, -0.315201f);
    glVertex2f( -3.09023f,  0.055759f);
    glVertex2f( -3.19410f,  0.471234f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f( -2.04704f, -0.606495f);
    glVertex2f( -1.79403f, -0.875934f);
    glVertex2f( -1.58413f, -1.531950f);
    glVertex2f( -1.47202f, -1.099370f);
    glVertex2f( -1.02549f, -1.731790f);
    glVertex2f( -1.02549f, -1.248240f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -2.10347f, -1.220340f);
    glVertex2f( -2.41505f, -0.047902f);
    glVertex2f( -2.25405f, -0.337056f);
    glVertex2f( -2.04704f, -0.606495f);
    glVertex2f( -1.58413f, -1.531950f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(  3.97311f,  2.811350f);
    glVertex2f(  5.00000f,  5.000000f);
    glVertex2f(  3.97311f, -2.811350f);
    glVertex2f(  5.00000f, -5.000000f);
    glVertex2f( -1.02549f, -2.811350f);
    glVertex2f( -5.00000f, -5.000000f);
    glVertex2f( -2.93443f, -1.205510f);
    glVertex2f( -3.29797f, -0.760353f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -1.02549f, -2.81135f);
    glVertex2f( -2.93443f, -1.20551f);
    glVertex2f( -2.41508f, -1.63582f);
    glVertex2f( -1.84380f, -1.96226f);
    glVertex2f( -1.02549f, -2.15912f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -5.000000f, -5.000000f);
    glVertex2f( -5.000000f,  5.000000f);
    glVertex2f( -3.973110f,  0.545426f);
    glVertex2f( -3.869240f,  0.204143f);
    glVertex2f( -3.609570f, -0.315201f);
    glVertex2f( -3.297970f, -0.760353f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f( 1.29669f, -1.079560f);
    glVertex2f( 1.69028f, -0.820916f);
    glVertex2f( 1.69028f, -1.653080f);
    glVertex2f( 2.00515f, -0.517290f);
    glVertex2f( 2.20194f, -1.450660f);
    glVertex2f( 2.43810f, -0.179928f);
    glVertex2f( 2.67425f, -1.214510f);
    glVertex2f( 3.34336f, -0.719707f);
    glVertex2f( 3.10721f, -0.955861f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f( -0.474465f, -2.15912f);
    glVertex2f( -0.198952f, -1.70930f);
    glVertex2f(  0.155277f, -2.10289f);
    glVertex2f(  0.273356f, -1.58560f);
    glVertex2f(  0.706303f, -1.97919f);
    glVertex2f(  0.863740f, -1.33820f);
    glVertex2f(  1.178610f, -1.83300f);
    glVertex2f(  1.296690f, -1.07956f);
    glVertex2f(  1.690280f, -1.65308f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -1.025490f, -2.15912f);
    glVertex2f( -1.025490f, -1.73179f);
    glVertex2f( -0.198952f, -1.70930f);
    glVertex2f( -0.474465f, -2.15912f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(  2.123230f,  0.494796f);
    glVertex2f(  1.926430f,  0.269888f);
    glVertex2f(  1.847710f,  0.832160f);
    glVertex2f(  1.690280f, -0.033738f);
    glVertex2f(  1.532840f,  1.124540f);
    glVertex2f(  1.324200f,  0.426719f);
    glVertex2f(  1.178610f,  1.394430f);
    glVertex2f(  1.012590f,  0.753164f);
    glVertex2f(  0.706303f,  1.709300f);
    glVertex2f(  0.649050f,  1.094450f);
    glVertex2f(  0.233576f,  1.361540f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f( -0.441573f, -0.879060f);
    glVertex2f( -0.078033f, -0.745515f);
    glVertex2f(  0.115919f, -1.113300f);
    glVertex2f(  0.389378f, -0.508100f);
    glVertex2f(  0.588227f, -0.899634f);
    glVertex2f(  0.804852f, -0.166817f);
    glVertex2f(  0.942455f, -0.652235f);
    glVertex2f(  1.064520f,  0.189305f);
    glVertex2f(  1.296690f, -0.348609f);
    glVertex2f(  1.324200f,  0.426719f);
    glVertex2f(  1.690280f, -0.033738f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -0.474465f, -1.259490f);
    glVertex2f( -1.025490f, -1.248240f);
    glVertex2f( -1.013530f, -0.889070f);
    glVertex2f( -0.441573f, -0.879060f);
    glVertex2f(  0.115919f, -1.113300f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(  0.706303f,  1.709300f);
    glVertex2f(  0.233576f,  1.361540f);
    glVertex2f(  0.076562f,  1.967940f);
    glVertex2f( -0.233835f,  1.598950f);
    glVertex2f( -0.395747f,  2.080400f);
    glVertex2f( -1.064780f,  1.658310f);
    glVertex2f( -1.064780f,  2.058940f);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f( -1.909030f,  0.076960f);
    glVertex2f( -1.863030f,  0.326685f);
    glVertex2f( -1.748030f, -0.159620f);
    glVertex2f( -1.610020f,  0.530407f);
    glVertex2f( -1.541020f, -0.448774f);
    glVertex2f( -1.380010f,  0.681555f);
    glVertex2f( -1.311010f, -0.685355f);
    glVertex2f( -1.012850f,  0.723487f);
    glVertex2f( -1.013530f, -0.889070f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -0.078033f, -0.107463f);
    glVertex2f( -0.233835f,  0.218981f);
    glVertex2f( -0.129966f,  1.005420f);
    glVertex2f(  0.285509f,  0.753164f);
    glVertex2f(  0.545180f,  0.441557f);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( -0.493508f,  0.560265f);
    glVertex2f( -1.012850f,  0.723487f);
    glVertex2f( -0.545442f,  1.153800f);
    glVertex2f( -0.129966f,  1.005420f);
    glVertex2f( -0.233835f,  0.218981f);
  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex2f( -0.545442f,  1.153800f);
    glVertex2f( -1.012850f,  0.723487f);
    glVertex2f( -1.035000f,  1.167860f);
    glVertex2f( -3.973110f,  0.545426f);
    glVertex2f( -5.000000f,  5.000000f);
    glVertex2f( -3.505700f,  0.960900f);
  glEnd();
}

static void makeNvidiaLogoVolume(void)
{
  glBegin(GL_QUAD_STRIP);
    glVertex3f( -5.000000f, -5.000000f, 0.0f); glVertex3f( -5.000000f, -5.000000f, 1.0f);
    glVertex3f( -5.000000f,  5.000000f, 0.0f); glVertex3f( -5.000000f,  5.000000f, 1.0f);
    glVertex3f(  5.000000f,  5.000000f, 0.0f); glVertex3f(  5.000000f,  5.000000f, 1.0f);
    glVertex3f(  5.000000f, -5.000000f, 0.0f); glVertex3f(  5.000000f, -5.000000f, 1.0f);
    glVertex3f( -5.000000f, -5.000000f, 0.0f); glVertex3f( -5.000000f, -5.000000f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f( -3.973110f,  0.545426f, 0.0f); glVertex3f( -3.973110f,  0.545426f, 1.0f);
    glVertex3f( -3.869240f,  0.204143f, 0.0f); glVertex3f( -3.869240f,  0.204143f, 1.0f);
    glVertex3f( -3.609570f, -0.315201f, 0.0f); glVertex3f( -3.609570f, -0.315201f, 1.0f);
    glVertex3f( -3.297970f, -0.760353f, 0.0f); glVertex3f( -3.297970f, -0.760353f, 1.0f);
    glVertex3f( -2.934430f, -1.205510f, 0.0f); glVertex3f( -2.934430f, -1.205510f, 1.0f);
    glVertex3f( -2.415080f, -1.635820f, 0.0f); glVertex3f( -2.415080f, -1.635820f, 1.0f);
    glVertex3f( -1.843800f, -1.962260f, 0.0f); glVertex3f( -1.843800f, -1.962260f, 1.0f);
    glVertex3f( -1.025490f, -2.159120f, 0.0f); glVertex3f( -1.025490f, -2.159120f, 1.0f);
    glVertex3f( -1.025490f, -2.811350f, 0.0f); glVertex3f( -1.025490f, -2.811350f, 1.0f);
    glVertex3f(  3.973110f, -2.811350f, 0.0f); glVertex3f(  3.973110f, -2.811350f, 1.0f);
    glVertex3f(  3.973110f,  2.811350f, 0.0f); glVertex3f(  3.973110f,  2.811350f, 1.0f);
    glVertex3f( -1.064850f,  2.811350f, 0.0f); glVertex3f( -1.064850f,  2.811350f, 1.0f);
    glVertex3f( -1.064780f,  2.058940f, 0.0f); glVertex3f( -1.064780f,  2.058940f, 1.0f);
    glVertex3f( -2.051540f,  1.851210f, 0.0f); glVertex3f( -2.051540f,  1.851210f, 1.0f);
    glVertex3f( -2.830560f,  1.435730f, 0.0f); glVertex3f( -2.830560f,  1.435730f, 1.0f);
    glVertex3f( -3.505700f,  0.960900f, 0.0f); glVertex3f( -3.505700f,  0.960900f, 1.0f);
    glVertex3f( -3.973110f,  0.545426f, 0.0f); glVertex3f( -3.973110f,  0.545426f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f( -2.570880f, -0.760353f, 0.0f); glVertex3f( -2.570880f,-0.760353f, 1.0f);
    glVertex3f( -2.830560f, -0.315201f, 0.0f); glVertex3f( -2.830560f,-0.315201f, 1.0f);
    glVertex3f( -3.090230f,  0.055759f, 0.0f); glVertex3f( -3.090230f, 0.055759f, 1.0f);
    glVertex3f( -3.194100f,  0.471234f, 0.0f); glVertex3f( -3.194100f, 0.471234f, 1.0f);
    glVertex3f( -2.830560f,  0.842190f, 0.0f); glVertex3f( -2.830560f, 0.842190f, 1.0f);
    glVertex3f( -2.363150f,  1.183480f, 0.0f); glVertex3f( -2.363150f, 1.183480f, 1.0f);
    glVertex3f( -1.791870f,  1.495080f, 0.0f); glVertex3f( -1.791870f, 1.495080f, 1.0f);
    glVertex3f( -1.064780f,  1.658310f, 0.0f); glVertex3f( -1.064780f, 1.658310f, 1.0f);
    glVertex3f( -1.035000f,  1.167860f, 0.0f); glVertex3f( -1.035000f, 1.167860f, 1.0f);
    glVertex3f( -1.633020f,  1.016710f, 0.0f); glVertex3f( -1.633020f, 1.016710f, 1.0f);
    glVertex3f( -2.047040f,  0.806418f, 0.0f); glVertex3f( -2.047040f, 0.806418f, 1.0f);
    glVertex3f( -2.392050f,  0.536978f, 0.0f); glVertex3f( -2.392050f, 0.536978f, 1.0f);
    glVertex3f( -2.530060f,  0.260968f, 0.0f); glVertex3f( -2.530060f, 0.260968f, 1.0f);
    glVertex3f( -2.415050f, -0.047902f, 0.0f); glVertex3f( -2.415050f,-0.047902f, 1.0f);
    glVertex3f( -2.254050f, -0.337056f, 0.0f); glVertex3f( -2.254050f,-0.337056f, 1.0f);
    glVertex3f( -2.047040f, -0.606495f, 0.0f); glVertex3f( -2.047040f,-0.606495f, 1.0f);
    glVertex3f( -1.794030f, -0.875934f, 0.0f); glVertex3f( -1.794030f,-0.875934f, 1.0f);
    glVertex3f( -1.472020f, -1.099370f, 0.0f); glVertex3f( -1.472020f,-1.099370f, 1.0f);
    glVertex3f( -1.025490f, -1.248240f, 0.0f); glVertex3f( -1.025490f,-1.248240f, 1.0f);
    glVertex3f( -1.025490f, -1.731790f, 0.0f); glVertex3f( -1.025490f,-1.731790f, 1.0f);
    glVertex3f( -1.584130f, -1.531950f, 0.0f); glVertex3f( -1.584130f,-1.531950f, 1.0f);
    glVertex3f( -2.103470f, -1.220340f, 0.0f); glVertex3f( -2.103470f,-1.220340f, 1.0f);
    glVertex3f( -2.570880f, -0.760353f, 0.0f); glVertex3f( -2.570880f,-0.760353f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f(  3.343360f, -0.719707f, 0.0f); glVertex3f(  3.343360f, -0.719707f, 1.0f);
    glVertex3f(  3.107210f, -0.955861f, 0.0f); glVertex3f(  3.107210f, -0.955861f, 1.0f);
    glVertex3f(  2.674250f, -1.214510f, 0.0f); glVertex3f(  2.674250f, -1.214510f, 1.0f);
    glVertex3f(  2.201940f, -1.450660f, 0.0f); glVertex3f(  2.201940f, -1.450660f, 1.0f);
    glVertex3f(  1.690270f, -1.653080f, 0.0f); glVertex3f(  1.690270f, -1.653080f, 1.0f);
    glVertex3f(  1.178610f, -1.833000f, 0.0f); glVertex3f(  1.178610f, -1.833000f, 1.0f);
    glVertex3f(  0.706303f, -1.979190f, 0.0f); glVertex3f(  0.706303f, -1.979190f, 1.0f);
    glVertex3f(  0.155277f, -2.102890f, 0.0f); glVertex3f(  0.155277f, -2.102890f, 1.0f);
    glVertex3f( -0.474465f, -2.159120f, 0.0f); glVertex3f(- 0.474465f, -2.159120f, 1.0f);
    glVertex3f( -1.025490f, -2.159120f, 0.0f); glVertex3f(- 1.025490f, -2.159120f, 1.0f);
    glVertex3f( -1.025490f, -1.731790f, 0.0f); glVertex3f(- 1.025490f, -1.731790f, 1.0f);
    glVertex3f( -0.198952f, -1.709300f, 0.0f); glVertex3f(- 0.198952f, -1.709300f, 1.0f);
    glVertex3f(  0.273356f, -1.585600f, 0.0f); glVertex3f(  0.273356f, -1.585600f, 1.0f);
    glVertex3f(  0.863740f, -1.338200f, 0.0f); glVertex3f(  0.863740f, -1.338200f, 1.0f);
    glVertex3f(  1.296690f, -1.079560f, 0.0f); glVertex3f(  1.296690f, -1.079560f, 1.0f);
    glVertex3f(  1.690270f, -0.820916f, 0.0f); glVertex3f(  1.690270f, -0.820916f, 1.0f);
    glVertex3f(  2.005150f, -0.517290f, 0.0f); glVertex3f(  2.005150f, -0.517290f, 1.0f);
    glVertex3f(  2.438100f, -0.179928f, 0.0f); glVertex3f(  2.438100f, -0.179928f, 1.0f);
    glVertex3f(  3.343360f, -0.719707f, 0.0f); glVertex3f(  3.343360f, -0.719707f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f(  1.532840f,  1.124540f, 0.0f); glVertex3f(  1.5328400f,  1.124540f, 1.0f);
    glVertex3f(  1.847710f,  0.832160f, 0.0f); glVertex3f(  1.8477100f,  0.832160f, 1.0f);
    glVertex3f(  2.123230f,  0.494796f, 0.0f); glVertex3f(  2.1232300f,  0.494796f, 1.0f);
    glVertex3f(  1.926430f,  0.269888f, 0.0f); glVertex3f(  1.9264300f,  0.269888f, 1.0f);
    glVertex3f(  1.690270f, -0.033738f, 0.0f); glVertex3f(  1.6902700f, -0.033738f, 1.0f);
    glVertex3f(  1.296690f, -0.348609f, 0.0f); glVertex3f(  1.2966900f, -0.348609f, 1.0f);
    glVertex3f(  0.942455f, -0.652235f, 0.0f); glVertex3f(  0.9424550f, -0.652235f, 1.0f);
    glVertex3f(  0.588227f, -0.899634f, 0.0f); glVertex3f(  0.5882270f, -0.899634f, 1.0f);
    glVertex3f(  0.115919f, -1.113300f, 0.0f); glVertex3f(  0.1159190f, -1.113300f, 1.0f);
    glVertex3f( -0.474465f, -1.259490f, 0.0f); glVertex3f( -0.4744650f, -1.259490f, 1.0f);
    glVertex3f( -1.025490f, -1.248240f, 0.0f); glVertex3f( -1.0254900f, -1.248240f, 1.0f);
    glVertex3f( -1.013530f, -0.889070f, 0.0f); glVertex3f( -1.0135300f, -0.889070f, 1.0f);
    glVertex3f( -0.441573f, -0.879060f, 0.0f); glVertex3f( -0.4415730f, -0.879060f, 1.0f);
    glVertex3f( -0.078033f, -0.745515f, 0.0f); glVertex3f( -0.0780330f, -0.745515f, 1.0f);
    glVertex3f(  0.389378f, -0.508100f, 0.0f); glVertex3f(  0.3893780f, -0.508100f, 1.0f);
    glVertex3f(  0.804852f, -0.166817f, 0.0f); glVertex3f(  0.8048520f, -0.166817f, 1.0f);
    glVertex3f(  1.064520f,  0.189305f, 0.0f); glVertex3f(  1.0645200f,  0.189305f, 1.0f);
    glVertex3f(  1.324200f,  0.426719f, 0.0f); glVertex3f(  1.3242000f,  0.426719f, 1.0f);
    glVertex3f(  1.012590f,  0.753164f, 0.0f); glVertex3f(  1.0125900f,  0.753164f, 1.0f);
    glVertex3f(  0.649050f,  1.094450f, 0.0f); glVertex3f(  0.6490500f,  1.094450f, 1.0f);
    glVertex3f(  0.233576f,  1.361540f, 0.0f); glVertex3f(  0.2335760f,  1.361540f, 1.0f);
    glVertex3f( -0.233835f,  1.598950f, 0.0f); glVertex3f( -0.2338350f,  1.598950f, 1.0f);
    glVertex3f( -1.064780f,  1.658310f, 0.0f); glVertex3f( -1.0647800f,  1.658310f, 1.0f);
    glVertex3f( -1.064780f,  2.058940f, 0.0f); glVertex3f( -1.0647800f,  2.058940f, 1.0f);
    glVertex3f( -0.395747f,  2.080400f, 0.0f); glVertex3f( -0.3957470f,  2.080400f, 1.0f);
    glVertex3f(  0.076562f,  1.967940f, 0.0f); glVertex3f(  0.0765620f,  1.967940f, 1.0f);
    glVertex3f(  0.706303f,  1.709300f, 0.0f); glVertex3f(  0.7063030f,  1.709300f, 1.0f);
    glVertex3f(  1.178610f,  1.394430f, 0.0f); glVertex3f(  1.1786100f,  1.394430f, 1.0f);
    glVertex3f(  1.532840f,  1.124540f, 0.0f); glVertex3f(  1.5328400f,  1.124540f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f( -1.012850f,  0.723487f, 0.0f); glVertex3f( -1.012850f,  0.723487f, 1.0f);
    glVertex3f( -1.013530f, -0.889070f, 0.0f); glVertex3f( -1.013530f, -0.889070f, 1.0f);
    glVertex3f( -1.311010f, -0.685355f, 0.0f); glVertex3f( -1.311010f, -0.685355f, 1.0f);
    glVertex3f( -1.541020f, -0.448774f, 0.0f); glVertex3f( -1.541020f, -0.448774f, 1.0f);
    glVertex3f( -1.748030f, -0.159620f, 0.0f); glVertex3f( -1.748030f, -0.159620f, 1.0f);
    glVertex3f( -1.909030f,  0.076960f, 0.0f); glVertex3f( -1.909030f,  0.076960f, 1.0f);
    glVertex3f( -1.863030f,  0.326685f, 0.0f); glVertex3f( -1.863030f,  0.326685f, 1.0f);
    glVertex3f( -1.610020f,  0.530407f, 0.0f); glVertex3f( -1.610020f,  0.530407f, 1.0f);
    glVertex3f( -1.380010f,  0.681555f, 0.0f); glVertex3f( -1.380010f,  0.681555f, 1.0f);
    glVertex3f( -1.012850f,  0.723487f, 0.0f); glVertex3f( -1.012850f,  0.723487f, 1.0f);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f(  0.545180f,  0.441557f, 0.0f); glVertex3f(  0.545180f,  0.441557f, 1.0f);
    glVertex3f( -0.078033f, -0.107463f, 0.0f); glVertex3f( -0.078033f, -0.107463f, 1.0f);
    glVertex3f( -0.233835f,  0.218981f, 0.0f); glVertex3f( -0.233835f,  0.218981f, 1.0f);
    glVertex3f( -0.493508f,  0.560265f, 0.0f); glVertex3f( -0.493508f,  0.560265f, 1.0f);
    glVertex3f( -1.012850f,  0.723487f, 0.0f); glVertex3f( -1.012850f,  0.723487f, 1.0f);
    glVertex3f( -1.035000f,  1.167860f, 0.0f); glVertex3f( -1.035000f,  1.167860f, 1.0f);
    glVertex3f( -0.545442f,  1.153800f, 0.0f); glVertex3f( -0.545442f,  1.153800f, 1.0f);
    glVertex3f( -0.129966f,  1.005420f, 0.0f); glVertex3f( -0.129966f,  1.005420f, 1.0f);
    glVertex3f(  0.285509f,  0.753164f, 0.0f); glVertex3f(  0.285509f,  0.753164f, 1.0f);
    glVertex3f(  0.545180f,  0.441557f, 0.0f); glVertex3f(  0.545180f,  0.441557f, 1.0f);
  glEnd();
}

void initNVidiaLogo(GLuint nvidialogo, GLuint nvidialogoVolume)
{
  glNewList(nvidialogo, GL_COMPILE);
    makeNvidiaLogo();
  glEndList();

  glNewList(nvidialogoVolume, GL_COMPILE);
    makeNvidiaLogoVolume();
  glEndList();
}

#endif