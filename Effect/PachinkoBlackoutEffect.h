#pragma once
#include "EffectSuper.h"

#include <DxLib.h>
#include <cstring>
#include <cmath>

class PachinkoBlackoutEffect : public EffectSuper
{
public:
	void Update() override
	{
		++frameCount_;
	}

	void Draw() override
	{
		const int width = 1920;
		const int height = 1080;
		const int centerX = width / 2;
		const int centerY = height / 2;
		const float pi = 3.14159265f;
		const int colBg = GetColor(20, 8, 42);
		const int colFrameGold = GetColor(255, 210, 60);
		const int colFrameRed = GetColor(210, 16, 36);
		const int colScan = GetColor(255, 70, 130);
		const int colRing = GetColor(255, 220, 120);
		const int colWarningBase = GetColor(255, 200, 40);
		const int colWarningInner = GetColor(135, 0, 45);
		const int colBand = GetColor(240, 20, 60);
		const int colBandEdge = GetColor(255, 210, 90);
		const int colFlash = GetColor(255, 80, 120);
		const int colTextDark = GetColor(90, 0, 25);
		auto drawCenterText = [centerX](int y, const char* text, int color)
		{
			const int textW = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));
			DrawString(centerX - textW / 2, y, text, color);
		};

		DrawBox(0, 0, width, height, colBg, TRUE);
		DrawBox(30, 30, width - 30, height - 30, colFrameGold, FALSE);
		DrawBox(50, 50, width - 50, height - 50, colFrameRed, FALSE);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 90);
		for (int i = -height; i < width; i += 36)
		{
			const int offset = (frameCount_ * 22) % 36;
			const int x1 = i + offset;
			const int y1 = 0;
			const int x2 = x1 + height;
			const int y2 = height;
			DrawLine(x1, y1, x2, y2, colScan, 2);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		float t = static_cast<float>(frameCount_) / static_cast<float>(kEffectFrames);
		if (t < 0.0f) t = 0.0f;
		if (t > 1.0f) t = 1.0f;

		{
			const float wave = (std::sin(frameCount_ * 0.24f) + 1.0f) * 0.5f;
			const int baseRadius = 120 + static_cast<int>(t * 230.0f);
			const int pulse = static_cast<int>(wave * 28.0f);

			SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
			for (int i = 0; i < 3; ++i)
			{
				const int r = baseRadius + pulse + i * 42;
				DrawCircle(centerX, centerY, r, colRing, FALSE, 3);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		if (frameCount_ < 36)
		{
			for (int i = 0; i < 8; ++i)
			{
				int y = 160 + i * 90;
				int x = (frameCount_ * 55 + i * 160) % (width + 300) - 300;
				DrawBox(x, y, x + 240, y + 12, colBand, TRUE);
				DrawBox(x, y + 12, x + 240, y + 16, colBandEdge, TRUE);
			}
			DrawBox(centerX - 250, centerY - 55, centerX + 250, centerY + 5, colWarningBase, TRUE);
			DrawBox(centerX - 235, centerY - 45, centerX + 235, centerY - 5, colWarningInner, TRUE);
			drawCenterText(centerY - 33, "WARNING", GetColor(255, 255, 255));
		}

		if (frameCount_ >= 28 && frameCount_ < 90)
		{
			int span = static_cast<int>((1.0f - (t - 0.22f) / 0.50f) * 900.0f);
			if (span < 20) span = 20;

			for (int i = 0; i < 6; ++i)
			{
				int y = centerY - 180 + i * 70;
				int h = 24;
				DrawBox(centerX - span, y, centerX + span, y + h, colBand, TRUE);
				DrawBox(centerX - span, y + h, centerX + span, y + h + 3, colBandEdge, TRUE);
			}

			DrawCircle(centerX, centerY, 220, colFrameGold, FALSE);
			DrawCircle(centerX, centerY, 180, colBand, FALSE);
			DrawBox(centerX - 300, centerY - 48, centerX + 300, centerY + 48, GetColor(255, 255, 255), TRUE);
			drawCenterText(centerY - 14, "PUCHUUN CHANCE", colTextDark);
		}

		if (frameCount_ >= 90)
		{
			int flash = 255 - (frameCount_ - 90) * 6;
			if (flash < 60) flash = 60;

			const int puchuunStart = 90;
			const int puchuunPeak = 108;
			const int puchuunEnd = kEffectFrames;
			int puchuunAlpha = 0;
			if (frameCount_ <= puchuunPeak)
			{
				const int denom = puchuunPeak - puchuunStart;
				if (denom > 0)
				{
					puchuunAlpha = (frameCount_ - puchuunStart) * 255 / denom;
				}
			}
			else
			{
				const int denom = puchuunEnd - puchuunPeak;
				if (denom > 0)
				{
					puchuunAlpha = (puchuunEnd - frameCount_) * 255 / denom;
				}
			}
			if (puchuunAlpha < 0) puchuunAlpha = 0;
			if (puchuunAlpha > 255) puchuunAlpha = 255;

			DrawBox(0, 0, width, height, GetColor(flash, flash / 3, flash / 2), TRUE);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, puchuunAlpha);
			DrawBox(centerX - 340, centerY - 90, centerX + 340, centerY + 90, colFlash, TRUE);
			DrawBox(centerX - 320, centerY - 72, centerX + 320, centerY + 72, colFrameGold, TRUE);
			drawCenterText(centerY - 12, "PUCHUUN !!!", colTextDark);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		if (frameCount_ >= 76)
		{
			const float flareT = static_cast<float>(frameCount_ - 76) / static_cast<float>(kEffectFrames - 76);
			float clampedFlareT = flareT;
			if (clampedFlareT < 0.0f) clampedFlareT = 0.0f;
			if (clampedFlareT > 1.0f) clampedFlareT = 1.0f;

			const int alpha = 60 + static_cast<int>(140.0f * clampedFlareT);
			const int span = 420 + static_cast<int>(520.0f * clampedFlareT);
			const int flareX = centerX + static_cast<int>(std::sin((frameCount_ - 76) * 0.12f * pi) * 90.0f);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawBox(flareX - span, centerY - 6, flareX + span, centerY + 6, GetColor(255, 245, 190), TRUE);
			DrawCircle(flareX - 220, centerY, 28, GetColor(255, 170, 180), TRUE);
			DrawCircle(flareX, centerY, 40, GetColor(255, 255, 220), TRUE);
			DrawCircle(flareX + 250, centerY, 20, GetColor(255, 195, 145), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		const int blackoutStart = 98;
		if (frameCount_ >= blackoutStart)
		{
			int blackoutAlpha = (frameCount_ - blackoutStart) * 255 / (kEffectFrames - blackoutStart);
			if (blackoutAlpha < 0) blackoutAlpha = 0;
			if (blackoutAlpha > 255) blackoutAlpha = 255;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackoutAlpha);
			DrawBox(0, 0, width, height, GetColor(0, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	bool IsFinished() const override
	{
		return frameCount_ >= kEffectFrames;
	}

private:
	int frameCount_ = 0;
	static const int kEffectFrames = 132;
};
