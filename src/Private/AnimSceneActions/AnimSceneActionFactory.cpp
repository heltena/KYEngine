#include <KYEngine/Private/AnimSceneActions/AddEntityAction.h>
#include <KYEngine/Private/AnimSceneActions/AddNewParticleEmitterAction.h>
#include <KYEngine/Private/AnimSceneActions/AddTextEntityAction.h>
#include <KYEngine/Private/AnimSceneActions/AddToggleButtonAction.h>
#include <KYEngine/Private/AnimSceneActions/AddTouchEventAction.h>
#include <KYEngine/Private/AnimSceneActions/AnimLoopAction.h>
#include <KYEngine/Private/AnimSceneActions/AnimSceneActionFactory.h>
#include <KYEngine/Private/AnimSceneActions/AsyncLoadResourcesAction.h>
#include <KYEngine/Private/AnimSceneActions/AsyncLoadScenesAction.h>
#include <KYEngine/Private/AnimSceneActions/BezierMoveAction.h>
#include <KYEngine/Private/AnimSceneActions/BlinkAction.h>
#include <KYEngine/Private/AnimSceneActions/BounceAction.h>
#include <KYEngine/Private/AnimSceneActions/ChangeAnimAction.h>
#include <KYEngine/Private/AnimSceneActions/ChangeColorAction.h>
#include <KYEngine/Private/AnimSceneActions/ChangeMusicAction.h>
#include <KYEngine/Private/AnimSceneActions/CreateTimerAction.h>
#include <KYEngine/Private/AnimSceneActions/EarnAchievementAction.h>
#include <KYEngine/Private/AnimSceneActions/ExecuteMiniScriptAction.h>
#include <KYEngine/Private/AnimSceneActions/FadeAction.h>
#include <KYEngine/Private/AnimSceneActions/FinishActionAction.h>
#include <KYEngine/Private/AnimSceneActions/FinishAllActiveActionsAction.h>
#include <KYEngine/Private/AnimSceneActions/HidePlayingHudAction.h>
#include <KYEngine/Private/AnimSceneActions/InitGameCenterAction.h>
#include <KYEngine/Private/AnimSceneActions/LoadGlobalResourcesAction.h>
#include <KYEngine/Private/AnimSceneActions/MoveAction.h>
#include <KYEngine/Private/AnimSceneActions/MoveParticleEmitterAction.h>
#include <KYEngine/Private/AnimSceneActions/PathAllAction.h>
#include <KYEngine/Private/AnimSceneActions/PathMoveAction.h>
#include <KYEngine/Private/AnimSceneActions/PlaySoundAction.h>
#include <KYEngine/Private/AnimSceneActions/PopMusicAction.h>
#include <KYEngine/Private/AnimSceneActions/PopSceneAction.h>
#include <KYEngine/Private/AnimSceneActions/PushAndSwitchToSceneAction.h>
#include <KYEngine/Private/AnimSceneActions/PushCurrentMusicAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllEntitiesAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllParticleEmittersAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllTouchEventsAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllToggleButtonEventsAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveEntityAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveParticleEmitterAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveTimerAction.h>
#include <KYEngine/Private/AnimSceneActions/ResumeHelpAction.h>
#include <KYEngine/Private/AnimSceneActions/RotateAction.h>
#include <KYEngine/Private/AnimSceneActions/ScaleAction.h>
#include <KYEngine/Private/AnimSceneActions/SetEntityInfoAction.h>
#include <KYEngine/Private/AnimSceneActions/SetHelpInfoAction.h>
#include <KYEngine/Private/AnimSceneActions/SetParamAction.h>
#include <KYEngine/Private/AnimSceneActions/SetLocaleAction.h>
#include <KYEngine/Private/AnimSceneActions/SetTextAction.h>
#include <KYEngine/Private/AnimSceneActions/ShowDialogAction.h>
#include <KYEngine/Private/AnimSceneActions/ShowPopupAction.h>
#include <KYEngine/Private/AnimSceneActions/SoundMuteAction.h>
#include <KYEngine/Private/AnimSceneActions/SoundUnmuteAction.h>
#include <KYEngine/Private/AnimSceneActions/StartHelpAction.h>
#include <KYEngine/Private/AnimSceneActions/StopMusicAction.h>
#include <KYEngine/Private/AnimSceneActions/SwitchToSceneAction.h>
#include <KYEngine/Private/AnimSceneActions/UnloadAllPreloadedResourceGroupsAction.h>
#include <KYEngine/Private/AnimSceneActions/UnlockHelpAction.h>
#include <KYEngine/Private/AnimSceneActions/UnlockMotionAction.h>
#include <KYEngine/Private/AnimSceneActions/UpdateEntitiesAction.h>
#include <KYEngine/Private/AnimSceneActions/UpdateGameCenterInfoAction.h>
#include <KYEngine/Private/AnimSceneActions/UseAtrezzoAction.h>
#include <KYEngine/Private/AnimSceneActions/UsePlayingHudAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForAbsoluteTimeAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForActionFinishedAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForHudDisappearedAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForMusicTimeValueAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForParamChangedAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTimeAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTimerValueAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTouchAction.h>
#include <KYEngine/Private/AnimSceneActions/WalkAction.h>

#include <KYEngine/Private/Resources/MeshEntityResource.h>
#include <KYEngine/Private/SceneTimeline.h>

#include <stdexcept>
#include <string>

Action* AnimSceneActionFactory::readFromXml(const std::string& prefix, TiXmlElement* node)
{
	const std::string& nodeValue = node->Value();
    
    std::string value;
    if (prefix.length() == 0) {
        value = nodeValue;
    } else {
        size_t dots = nodeValue.find_first_of(':');
        if (dots == std::string::npos)
            throw std::runtime_error("AnimSceneActionFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        if (nodeValue.substr(0, dots) != prefix)
            throw std::runtime_error("AnimSceneActionFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        value = nodeValue.substr(dots + 1);
    }

    /**/ if (value == AddEntityAction::XML_NODE)                return AddEntityAction::readFromXml(node);
    else if (value == AddNewParticleEmitterAction::XML_NODE)    return AddNewParticleEmitterAction::readFromXml(node);
    else if (value == AddTextEntityAction::XML_NODE)            return AddTextEntityAction::readFromXml(node);
    else if (value == AddToggleButtonAction::XML_NODE)          return AddToggleButtonAction::readFromXml(node);
	else if (value == AddTouchEventAction::XML_NODE)            return AddTouchEventAction::readFromXml(node);
    else if (value == AnimLoopAction::XML_NODE)					return AnimLoopAction::readFromXml(node);
    else if (value == AsyncLoadResourcesAction::XML_NODE)       return AsyncLoadResourcesAction::readFromXml(node);
    else if (value == AsyncLoadScenesAction::XML_NODE)          return AsyncLoadScenesAction::readFromXml(node);
    else if (value == BezierMoveAction::XML_NODE)               return BezierMoveAction::readFromXml(node);
    else if (value == BlinkAction::XML_NODE)                    return BlinkAction::readFromXml(node);
    else if (value == BounceAction::XML_NODE)                   return BounceAction::readFromXml(node);
	else if (value == ChangeAnimAction::XML_NODE)               return ChangeAnimAction::readFromXml(node);
    else if (value == ChangeColorAction::XML_NODE)              return ChangeColorAction::readFromXml(node);
	else if (value == ChangeMusicAction::XML_NODE)              return ChangeMusicAction::readFromXml(node);
    else if (value == CreateTimerAction::XML_NODE)              return CreateTimerAction::readFromXml(node);
    else if (value == EarnAchievementAction::XML_NODE)          return EarnAchievementAction::readFromXml(node);
    else if (value == ExecuteMiniScriptAction::XML_NODE)        return ExecuteMiniScriptAction::readFromXml(node);
	else if (value == FadeAction::XML_NODE)                     return FadeAction::readFromXml(node);
    else if (value == FinishActionAction::XML_NODE)             return FinishActionAction::readFromXml(node);
    else if (value == FinishAllActiveActionsAction::XML_NODE)   return FinishAllActiveActionsAction::readFromXml(node);
    else if (value == HidePlayingHudAction::XML_NODE)           return HidePlayingHudAction::readFromXml(node);
    else if (value == InitGameCenterAction::XML_NODE)           return InitGameCenterAction::readFromXml(node);
    else if (value == LoadGlobalResourcesAction::XML_NODE)      return LoadGlobalResourcesAction::readFromXml(node);
	else if (value == MoveAction::XML_NODE)                     return MoveAction::readFromXml(node);
    else if (value == MoveParticleEmitterAction::XML_NODE)      return MoveParticleEmitterAction::readFromXml(node);
    else if (value == PathAllAction::XML_NODE)                  return PathAllAction::readFromXml(node);
    else if (value == PathMoveAction::XML_NODE)                 return PathMoveAction::readFromXml(node);
	else if (value == PlaySoundAction::XML_NODE)                return PlaySoundAction::readFromXml(node);
    else if (value == PopMusicAction::XML_NODE)                 return PopMusicAction::readFromXml(node);
    else if (value == PopSceneAction::XML_NODE)                 return PopSceneAction::readFromXml(node);
    else if (value == PushAndSwitchToSceneAction::XML_NODE)     return PushAndSwitchToSceneAction::readFromXml(node);
    else if (value == PushCurrentMusicAction::XML_NODE)         return PushCurrentMusicAction::readFromXml(node);
    else if (value == RemoveAllEntitiesAction::XML_NODE)        return RemoveAllEntitiesAction::readFromXml(node);
    else if (value == RemoveAllParticleEmittersAction::XML_NODE) return RemoveAllParticleEmittersAction::readFromXml(node);
    else if (value == RemoveAllToggleButtonEventsAction::XML_NODE) return RemoveAllToggleButtonEventsAction::readFromXml(node);
	else if (value == RemoveAllTouchEventsAction::XML_NODE)     return RemoveAllTouchEventsAction::readFromXml(node);
	else if (value == RemoveEntityAction::XML_NODE)             return RemoveEntityAction::readFromXml(node);
    else if (value == RemoveParticleEmitterAction::XML_NODE)    return RemoveParticleEmitterAction::readFromXml(node);
    else if (value == RemoveTimerAction::XML_NODE)              return RemoveTimerAction::readFromXml(node);
    else if (value == ResumeHelpAction::XML_NODE)               return ResumeHelpAction::readFromXml(node);
    else if (value == RotateAction::XML_NODE)                   return RotateAction::readFromXml(node);
    else if (value == ScaleAction::XML_NODE)                    return ScaleAction::readFromXml(node);
    else if (value == SetEntityInfoAction::XML_NODE)            return SetEntityInfoAction::readFromXml(node);
    else if (value == SetHelpInfoAction::XML_NODE)              return SetHelpInfoAction::readFromXml(node);
	else if (value == SetLocaleAction::XML_NODE)                return SetLocaleAction::readFromXml(node);
	else if (value == SetParamAction::XML_NODE)                 return SetParamAction::readFromXml(node);
	else if (value == SetTextAction::XML_NODE)                  return SetTextAction::readFromXml(node);
    else if (value == ShowDialogAction::XML_NODE)               return ShowDialogAction::readFromXml(node);
    else if (value == ShowPopupAction::XML_NODE)                 return ShowPopupAction::readFromXml(node);
    else if (value == SoundMuteAction::XML_NODE)                return SoundMuteAction::readFromXml(node);
    else if (value == SoundUnmuteAction::XML_NODE)              return SoundUnmuteAction::readFromXml(node);
    else if (value == StartHelpAction::XML_NODE)                return StartHelpAction::readFromXml(node);
    else if (value == StopMusicAction::XML_NODE)                return StopMusicAction::readFromXml(node);
	else if (value == SwitchToSceneAction::XML_NODE)            return SwitchToSceneAction::readFromXml(node);
    else if (value == UnloadAllPreloadedResourceGroupsAction::XML_NODE) return UnloadAllPreloadedResourceGroupsAction::readFromXml(node);
    else if (value == UnlockHelpAction::XML_NODE)               return UnlockHelpAction::readFromXml(node);
    else if (value == UnlockMotionAction::XML_NODE)             return UnlockMotionAction::readFromXml(node);
    else if (value == UpdateEntitiesAction::XML_NODE)           return UpdateEntitiesAction::readFromXml(node);
    else if (value == UpdateGameCenterInfoAction::XML_NODE)     return UpdateGameCenterInfoAction::readFromXml(node);
    else if (value == UseAtrezzoAction::XML_NODE)               return UseAtrezzoAction::readFromXml(node);
    else if (value == UsePlayingHudAction::XML_NODE)            return UsePlayingHudAction::readFromXml(node);
    else if (value == WaitForAbsoluteTimeAction::XML_NODE)      return WaitForAbsoluteTimeAction::readFromXml(node);
	else if (value == WaitForActionFinishedAction::XML_NODE)	return WaitForActionFinishedAction::readFromXml(node);
    else if (value == WaitForHudDisappearedAction::XML_NODE)    return WaitForHudDisappearedAction::readFromXml(node);
    else if (value == WaitForMusicTimeValueAction::XML_NODE)    return WaitForMusicTimeValueAction::readFromXml(node);
	else if (value == WaitForParamChangedAction::XML_NODE)		return WaitForParamChangedAction::readFromXml(node);
	else if (value == WaitForTimeAction::XML_NODE)              return WaitForTimeAction::readFromXml(node);
    else if (value == WaitForTimerValueAction::XML_NODE)        return WaitForTimerValueAction::readFromXml(node);
	else if (value == WaitForTouchAction::XML_NODE)             return WaitForTouchAction::readFromXml(node);
    else if (value == WalkAction::XML_NODE)                     return WalkAction::readFromXml(node);
	else
		throw std::runtime_error("AnimSceneFactory action name error: " + value);;
}
