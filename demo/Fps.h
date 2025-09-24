#pragma once

#include <chrono>

class Fps
{
public:
	Fps()
	{
		init();
	}

	void init() {
		mLastTime = std::chrono::high_resolution_clock::now();
		mFrameCount = 0;
		mFPS = 0.0f;
		mMS = 0.0f;
	}

	bool onFrame() {

		++mFrameCount;

		auto now = std::chrono::high_resolution_clock::now();
		float elapsed = (float)(std::chrono::duration<double, std::milli>(now - mLastTime).count());

		if (elapsed > 1000.0f) {
			mFPS = mFrameCount * 1000.0f / elapsed;
			mMS = elapsed / mFrameCount;
			mLastTime = now;
			mFrameCount = 0;
			return true;
		}

		return false;
	}

	float getFPS() const {
		return mFPS;
	}

	float getMS() const {
		return mMS;
	}

private:
	std::chrono::high_resolution_clock::time_point mLastTime;
	unsigned int mFrameCount = 0;
	float mFPS = 0.0f;
	float mMS = 0.0f;
};
