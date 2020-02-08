#pragma once

class SceneTimelineInfo;

class ActionBlockedListener
{
public:
	virtual void actionUnblocked(SceneTimelineInfo* info) = 0;
};