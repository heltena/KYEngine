#pragma once

#include <string>

class Core;
class SceneManager;

class ConcretGame
{
public:
    virtual ~ConcretGame() { }
    virtual const std::string appId() const = 0;
    virtual const std::string buyFullAppId() const = 0;
    virtual const std::string buyLiteAppId() const = 0;
    virtual const std::string buyButtonPressedScript() const = 0;
	virtual void initGame(Core& core) = 0;
};