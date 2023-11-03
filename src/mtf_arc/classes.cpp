/*  Revil Format Library
    Copyright(C) 2020-2021 Lukas Cone

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include "revil/hashreg.hpp"
#include <map>

using revil::Platform;

static auto MakeHashV1(std::string_view name) {
  return std::make_pair(revil::MTHashV1(name), name);
}

static auto MakeHashV2(std::string_view name) {
  return std::make_pair(revil::MTHashV2(name), name);
}

static const std::map<uint32, std::string_view> classNames{
    MakeHashV1("MtArray"),
    MakeHashV1("nodeData"),
    MakeHashV1("nodeHead"),
    MakeHashV1("nodeLink"),
    MakeHashV1("rAreaHitLayout::LayoutInfo"),
    MakeHashV1("rAreaSetLayout::LayoutInfo"),
    MakeHashV1("rHavokConstraintLayout::LayoutInfo"),
    MakeHashV1("rHavokLinkCollisionLayout::LayoutInfo"),
    MakeHashV1("rReverb::cReverbData"),
    MakeHashV1("rSceneBoxLayout::LayoutInfo"),
    MakeHashV1("rScrList::ScrListTable"),
    MakeHashV1("rSoundSeg::LayoutInfo"),
    MakeHashV1("sprMap"),
    MakeHashV1("sprMapHead"),
    MakeHashV2("cAIConditionTreeNode"),
    MakeHashV2("cAIDEnum"),
    MakeHashV2("cAIFSMCluster"),
    MakeHashV2("cAIFSMLink"),
    MakeHashV2("cAIFSMNode"),
    MakeHashV2("cAIPlanEvaluateAIParam"),
    MakeHashV2("cAIPlanEvaluateAttackRemain"),
    MakeHashV2("cAIPlanEvaluateAvoidLOF"),
    MakeHashV2("cAIPlanEvaluateCursorThrough"),
    MakeHashV2("cAIPlanEvaluateDamageRemain"),
    MakeHashV2("cAIPlanEvaluateDangerArea"),
    MakeHashV2("cAIPlanEvaluateDangerousTarget"),
    MakeHashV2("cAIPlanEvaluateDataPostOn"),
    MakeHashV2("cAIPlanEvaluateDefault"),
    MakeHashV2("cAIPlanEvaluateDistans"),
    MakeHashV2("cAIPlanEvaluateGetWp"),
    MakeHashV2("cAIPlanEvaluateHelpFriendHarmo"),
    MakeHashV2("cAIPlanEvaluateMessagePickUp"),
    MakeHashV2("cAIPlanEvaluateObject"),
    MakeHashV2("cAIPlanEvaluateReleaseWp"),
    MakeHashV2("cAIPlanEvaluateReload"),
    MakeHashV2("cAIPlanEvaluateWpChange"),
    MakeHashV2("cAIPlanFilterAIParam"),
    MakeHashV2("cAIPlanFilterArea"),
    MakeHashV2("cAIPlanFilterAvoidLOF"),
    MakeHashV2("cAIPlanFilterDataPostBOT"),
    MakeHashV2("cAIPlanFilterDefenceAkEgg"),
    MakeHashV2("cAIPlanFilterDevelop"),
    MakeHashV2("cAIPlanFilterDevelop"),
    MakeHashV2("cAIPlanFilterDir"),
    MakeHashV2("cAIPlanFilterDistans"),
    MakeHashV2("cAIPlanFilterEpisode"),
    MakeHashV2("cAIPlanFilterFSM"),
    MakeHashV2("cAIPlanFilterGetAkEgg"),
    MakeHashV2("cAIPlanFilterGetWp"),
    MakeHashV2("cAIPlanFilterGK"),
    MakeHashV2("cAIPlanFilterHelpEnergy"),
    MakeHashV2("cAIPlanFilterHm40Type"),
    MakeHashV2("cAIPlanFilterCharIsXXX"),
    MakeHashV2("cAIPlanFilterCharStatus"),
    MakeHashV2("cAIPlanFilterIsAction"),
    MakeHashV2("cAIPlanFilterIsAction"),
    MakeHashV2("cAIPlanFilterIsPlayerAuto"),
    MakeHashV2("cAIPlanFilterMessagePickUp"),
    MakeHashV2("cAIPlanFilterNetRecieveDataPost"),
    MakeHashV2("cAIPlanFilterObject"),
    MakeHashV2("cAIPlanFilterPartyLevel"),
    MakeHashV2("cAIPlanFilterPowerGroup"),
    MakeHashV2("cAIPlanFilterReleaseWp"),
    MakeHashV2("cAIPlanFilterReload"),
    MakeHashV2("cAIPlanFilterRunToReaderBot"),
    MakeHashV2("cAIPlanFilterRunToTargetBot"),
    MakeHashV2("cAIPlanFilterSeExist"),
    MakeHashV2("cAIPlanFilterSnekingLevel"),
    MakeHashV2("cAIPlanFilterTargetDir"),
    MakeHashV2("cAIPlanFilterTargetExist"),
    MakeHashV2("cAIPlanFilterTargetLifeMaxOverCk"),
    MakeHashV2("cAIPlanFilterTeamCommand"),
    MakeHashV2("cAIPlanFilterTracePos"),
    MakeHashV2("cAIPlanFilterTrue"),
    MakeHashV2("cAIPlanFilterUniqueIdRand"),
    MakeHashV2("cAIPlanFilterWeapon"),
    MakeHashV2("cAIPlanFilterWpChange"),
    MakeHashV2("cAIPlanFilterYattaEnd"),
    MakeHashV2("cAIPlanMoveAction"),
    MakeHashV2("cAIPlanMoveActionFreeJump"),
    MakeHashV2("cAIPlanMoveAk64Action"),
    MakeHashV2("cAIPlanMoveAreaInfoRefresh"),
    MakeHashV2("cAIPlanMoveAvoidLOF"),
    MakeHashV2("cAIPlanMoveDamage"),
    MakeHashV2("cAIPlanMoveDistance"),
    MakeHashV2("cAIPlanMoveFSMCommandSet"),
    MakeHashV2("cAIPlanMoveHarmoControl"),
    MakeHashV2("cAIPlanMoveHm40VoiceReq"),
    MakeHashV2("cAIPlanMoveHmAction"),
    MakeHashV2("cAIPlanMoveJumpControl"),
    MakeHashV2("cAIPlanMoveObject"),
    MakeHashV2("cAIPlanMovePickMessage"),
    MakeHashV2("cAIPlanMoveSendCommand"),
    MakeHashV2("cAIPlanMoveSendMessage"),
    MakeHashV2("cAIPlanMoveSetCursorMode"),
    MakeHashV2("cAIPlanMoveShot"),
    MakeHashV2("cAIPlanMoveShotEnergy"),
    MakeHashV2("cAIPlanMoveShotGranade"),
    MakeHashV2("cAIPlanMoveSuitWayPoint"),
    MakeHashV2("cAIPlanMoveTargetExist"),
    MakeHashV2("cAIPlanMoveTargetPosSetDir"),
    MakeHashV2("cAIPlanMoveTime"),
    MakeHashV2("cAIPlanMoveTrace"),
    MakeHashV2("cAIPlanMoveWaitPos"),
    MakeHashV2("cAIPlanReturnX"),
    MakeHashV2("cAIPositionEvaluationFunc"),
    MakeHashV2("cAIPositionEvaluationFuncList"),
    MakeHashV2("cFSMArea::MissionCycleSetParameter"),
    MakeHashV2("cFSMArea::UvScrollParameter"),
    MakeHashV2("cFSMArea::WarPointSetParameter"),
    MakeHashV2("cFSMFighter::AIDataPostUpParameter"),
    MakeHashV2("cFSMFighter::AIMovePositionParameter"),
    MakeHashV2("cFSMFighter::AIPermitSetParameter"),
    MakeHashV2("cFSMFighter::AIPlayerPursuitParameter"),
    MakeHashV2("cFSMFighter::AIPlayerSupportParameter"),
    MakeHashV2("cFSMFighter::AITraceMoveParameter"),
    MakeHashV2("cFSMFighter::CharParamSetParameter"),
    MakeHashV2("cFSMHM::ActionSetParameter"),
    MakeHashV2("cFSMHM::DamageActionSetParameter"),
    MakeHashV2("cFSMHM::MovePositionParameter"),
    MakeHashV2("cFSMCharacterBase::ActSetParameter"),
    MakeHashV2("cFSMCharacterBase::AttackPlayerKeepParameter"),
    MakeHashV2("cFSMCharacterBase::BlendMotionParameter"),
    MakeHashV2("cFSMCharacterBase::CalcPartsDamageSetParameter"),
    MakeHashV2("cFSMCharacterBase::CompulsionMoveParameter"),
    MakeHashV2("cFSMCharacterBase::EffectSetParameter"),
    MakeHashV2("cFSMCharacterBase::EffectSetResParameter"),
    MakeHashV2("cFSMCharacterBase::EffectSynchroSetParameter"),
    MakeHashV2("cFSMCharacterBase::CharListParentOfsParameter"),
    MakeHashV2("cFSMCharacterBase::CharListParentParameter"),
    MakeHashV2("cFSMCharacterBase::CheckPosSetParameter"),
    MakeHashV2("cFSMCharacterBase::InitPosSetParameter"),
    MakeHashV2("cFSMCharacterBase::MotionParameter"),
    MakeHashV2("cFSMCharacterBase::MoveScrollActiveParameter"),
    MakeHashV2("cFSMCharacterBase::ObjAdjustEntryParameter"),
    MakeHashV2("cFSMCharacterBase::PartsDispSetParameter"),
    MakeHashV2("cFSMCharacterBase::PosAngleFlagParameter"),
    MakeHashV2("cFSMCharacterBase::RequestSeParameter"),
    MakeHashV2("cFSMCharacterBase::ScaleSetParameter"),
    MakeHashV2("cFSMCharacterBase::ShotReqSetParameter"),
    MakeHashV2("cFSMCharacterBase::ShotSetParameter"),
    MakeHashV2("cFSMCharacterBase::ShotTargetSetParameter"),
    MakeHashV2("cFSMCharacterBase::ShotTargetSetZParameter"),
    MakeHashV2("cFSMCharacterBase::TargetSetParameter"),
    MakeHashV2("cFSMCharacterBase::TransLucenceParameter"),
    MakeHashV2("cFSMCharacterBase::UserWorkSetParameter"),
    MakeHashV2("cFSMCharacterBase::WepMotionParameter"),
    MakeHashV2("cFSMOM::BoatHitSetParameter"),
    MakeHashV2("cFSMOM::BoatRideModeSetParameter"),
    MakeHashV2("cFSMOM::ScrCollisionSetParameter"),
    MakeHashV2("cFSMOM::TrainHitSetParameter"),
    MakeHashV2("cFSMOrder::AngleParameter"),
    MakeHashV2("cFSMOrder::AreaHitSetParameter"),
    MakeHashV2("cFSMOrder::BaseRespawnPointSetParameter"),
    MakeHashV2("cFSMOrder::BoolParameter"),
    MakeHashV2("cFSMOrder::CallRequestSetParameter"),
    MakeHashV2("cFSMOrder::CameraMotionSetParameter"),
    MakeHashV2("cFSMOrder::CameraVibSetParameter"),
    MakeHashV2("cFSMOrder::CounterParameter"),
    MakeHashV2("cFSMOrder::F32Parameter"),
    MakeHashV2("cFSMOrder::FlagParameter"),
    MakeHashV2("cFSMOrder::PositionParameter"),
    MakeHashV2("cFSMOrder::RandomGetParameter"),
    MakeHashV2("cFSMOrder::ReqEventExecParameter"),
    MakeHashV2("cFSMOrder::S32Parameter"),
    MakeHashV2("cFSMOrder::ShellParameter"),
    MakeHashV2("cFSMOrder::SchedulerCloseParameter"),
    MakeHashV2("cFSMOrder::SchedulerParameter"),
    MakeHashV2("cFSMOrder::StatusFlagParameter"),
    MakeHashV2("cFSMOrder::SubMixerParameter"),
    MakeHashV2("cFSMOrder::TimerParameter"),
    MakeHashV2("cFSMVS::ActionSetParameter"),
    MakeHashV2("cFSMVS::AreaMoveAttackParameter"),
    MakeHashV2("cFSMVS::CannonShotSetParameter"),
    MakeHashV2("cFSMVS::CannonTargetSetParameter"),
    MakeHashV2("cFSMVS::MovePositionParameter"),
    MakeHashV2("cPositionEvaluationDangerMessageRange"),
    MakeHashV2("cPositionEvaluationDangerRange"),
    MakeHashV2("cPositionEvaluationDistToPos"),
    MakeHashV2("cPositionEvaluationPlayerVisibility"),
    MakeHashV2("cPositionEvaluationTargetGoodDistans"),
    MakeHashV2("cPositionEvaluationTargetRange"),
    MakeHashV2("cPositionEvaluationTargetVisibility"),
    MakeHashV2("cPositionFilterDoughnutAroundPos"),
    MakeHashV2("cPositionFilterDoughnutAroundPosTerritory"),
    MakeHashV2("cTargetVisibilityHigh"),
    MakeHashV2("cTargetVisibilityLow"),
    MakeHashV2("MtArray"),
    MakeHashV2("rAIConditionTree::ConstF32Node"),
    MakeHashV2("rAIConditionTree::ConstS32Node"),
    MakeHashV2("rAIConditionTree::ConstStringNode"),
    MakeHashV2("rAIConditionTree::OperationNode"),
    MakeHashV2("rAIConditionTree::StateNode"),
    MakeHashV2("rAIConditionTree::TreeInfo"),
    MakeHashV2("rAIConditionTree::VariableNode::VariableInfo"),
    MakeHashV2("rAIConditionTree::VariableNode"),
    MakeHashV2("rAIConditionTree"),
    MakeHashV2("rAreaBarrierEdit::Work"),
    MakeHashV2("rAreaHitLayout::LayoutInfo"),
    MakeHashV2("rAreaSetLayout::LayoutInfo"),
    MakeHashV2("rCnsIK::JointInfo"),
    MakeHashV2("rEffectProvider::E2DGroup"),
    MakeHashV2("rEffectProvider::E2DMaterial"),
    MakeHashV2("rEffectProvider::EffectList"),
    MakeHashV2("rEffectProvider::EffectLODParam"),
    MakeHashV2("rEffectProvider::EffectMotSyncParam"),
    MakeHashV2("rEffectProvider::EffectParam"),
    MakeHashV2("rEffectProvider::EffectSet"),
    MakeHashV2("rEffectProvider::INFO_E2D"),
    MakeHashV2("rEffectProvider::INFO_EFFECT"),
    MakeHashV2("rEffectProvider::INFO_PROV"),
    MakeHashV2("rFieldSet::E2DSetWork"),
    MakeHashV2("rFieldSet::FieldSetWork"),
    MakeHashV2("rHavokConstraintLayout::LayoutInfo"),
    MakeHashV2("rHavokLinkCollisionLayout::LayoutInfo"),
    MakeHashV2("rHmGenerator::EquipWeaponInfo"),
    MakeHashV2("rHmGenerator::HmGeneratorInfo"),
    MakeHashV2("rInitPosSet::InitPosSetInfo"),
    MakeHashV2("rPlanetEQ::cEQData"),
    MakeHashV2("rPlanetReverb::cReverbParam"),
    MakeHashV2("rPlanetReverb::cSoundReverbData"),
    MakeHashV2("rScrList::ScrListTable"),
    MakeHashV2("rSoundMotionSe::cSoundMotionSeData"),
    MakeHashV2("rSoundSequenceSe::SequenceSe::Command"),
    MakeHashV2("rSoundSequenceSe::SequenceSe"),
    MakeHashV2("rSoundSubMixer::Param"),
    MakeHashV2("rTexDetailEdit::DetailParam"),
    MakeHashV2("rThinkPlanAI::cItemPlanInfo"),
    MakeHashV2("rThinkPlanAI::cU32"),
    MakeHashV2("uAmbientLight"),
    MakeHashV2("uAnaglyphFilter"),
    MakeHashV2("uBaseModel"),
    MakeHashV2("uBloomFilter"),
    MakeHashV2("uBlurFilter"),
    MakeHashV2("uBlurFilterEx"),
    MakeHashV2("uBokehFilter"),
    MakeHashV2("uCapsuleLight"),
    MakeHashV2("uChrColorType"),
    MakeHashV2("uChrUvOffset"),
    MakeHashV2("uColorCorrectFilter"),
    MakeHashV2("uColorFog"),
    MakeHashV2("uCrossFadeFilter"),
    MakeHashV2("uCuboidShadowRegion"),
    MakeHashV2("uDOFFilter"),
    MakeHashV2("uEffect"),
    MakeHashV2("uFishEyeFilter"),
    MakeHashV2("uGameEffect"),
    MakeHashV2("uHemiSphereLight"),
    MakeHashV2("uInfiniteLight"),
    MakeHashV2("uMaterialControl"),
    MakeHashV2("uMaterialControlEx"),
    MakeHashV2("uMaterialVjobCngColor"),
    MakeHashV2("uModel"),
    MakeHashV2("uMvc3LightSpaceShadow"),
    MakeHashV2("uOutlineFilter"),
    MakeHashV2("uPointLight"),
    MakeHashV2("uRadialBlurFilter"),
    MakeHashV2("uScheduler"),
    MakeHashV2("uSpotLight"),
    MakeHashV2("uStageObject"),
    MakeHashV2("uStageStaticModel"),
    MakeHashV2("uStgObj010_LaboDust"),
    MakeHashV2("uStgObj010_LickerCmn"),
    MakeHashV2("uStgObj011_BreakGround"),
    MakeHashV2("uStgObj011_Earth"),
    MakeHashV2("uStgObj102_Monitor"),
    MakeHashV2("uTVNoiseFilter"),
    MakeHashV2("uToonLight"),
    MakeHashV2("uUiAnmSprite"),
    MakeHashV2("uUiAnmSpriteFont"),
    MakeHashV2("uUiAnmSpriteFrame"),
    MakeHashV2("uUiAnmSpriteRadar"),
    MakeHashV2("uUiDepthClear"),
    MakeHashV2("uUiEffectBase"),
    MakeHashV2("uUiModelBase"),
    MakeHashV2("uUiSdlAnimeFrame"),
    MakeHashV2("uUiSprite"),
    MakeHashV2("uUiSprite3D"),
    MakeHashV2("uXFactorOutlineFilter"),
};

using pair_type = std::pair<std::string_view, std::string_view>;

std::pair<uint32 const, pair_type> GetPair(uint32 hash, Platform platform);

namespace revil {
std::string_view GetClassName(uint32 hash, Platform platform) {
  auto pair = GetPair(hash, platform);

  if (pair.first) {
    return pair.second.second;
  }

  auto found = classNames.find(hash);

  if (!es::IsEnd(classNames, found)) {
    return found->second;
  }

  return {};
}
} // namespace revil
