#pragma once

class EffectSuper
{
public:
	virtual ~EffectSuper() = default;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsFinished() const = 0;
};
