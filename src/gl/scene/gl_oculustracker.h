#ifndef GZDOOM_OCULUS_TRACKER_H_
#define GZDOOM_OCULUS_TRACKER_H_

#ifdef HAVE_OCULUS_API
#include "OVR.h"
#endif

class OculusTexture;

class OculusTracker {
public:
	OculusTracker();
	~OculusTracker();
	float getPositionX();
	float getPositionY();
	float getPositionZ();
	void resetPosition();
	void beginFrame();
	void endFrame();
	void configureTexture(OculusTexture*);
#ifdef HAVE_OCULUS_API
	// const OVR::HMDInfo& getInfo() const {return Info;}
	float getRiftInterpupillaryDistance() const {
		const_cast<OculusTracker&>(*this).checkConfiguration();
		return ovrHmd_GetFloat(hmd, OVR_KEY_IPD, 0.062f);
	}
	OVR::Quatf quaternion;
#endif
	bool isGood() const;
	void update();
	int getDeviceId() const {return deviceId;}

	// Head orientation state, refreshed by call to update();
	float pitch, roll, yaw;
	void setLowPersistence(bool setLow);
	void checkInitialized();
	void checkConfiguration();
	void checkHealthAndSafety();

private:
	bool trackingConfigured;
	bool renderingConfigured;
	bool ovrInitialized;
#ifdef HAVE_OCULUS_API
	ovrHmd hmd;
	// ovrHmdDesc hmdDesc;
	// ovrSensorDesc sensorDesc;
	int deviceId;
	OVR::Vector3f position;
	OVR::Vector3f originPosition;
	ovrPosef eyePose;
	int frameIndex;
	int texWidth, texHeight, textureId; // for oculus offscreen texture


	// OVR::Ptr<OVR::DeviceManager> pManager;
	// OVR::Ptr<OVR::HMDDevice> pHMD;
	// OVR::Ptr<OVR::SensorDevice> pSensor;
	// OVR::SensorFusion* pFusionResult;
	// OVR::HMDInfo Info;
	// bool InfoLoaded;
#endif
};

extern OculusTracker * sharedOculusTracker;

#endif // GZDOOM_OCULUS_TRACKER_H_
