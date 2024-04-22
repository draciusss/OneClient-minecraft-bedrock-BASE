#pragma once
//#include "../../../entt/entt.hpp" // Including entt here to avoid overriding.

#include "../../Components/StateVectorComponent.h"
#include "../../Components/AABBShapeComponent.h"
#include "../../Components/ActorDefinitionIdentifierComponent.h"
#include "../../Components/ActorOwnerComponent.h"
#include "../../Components/RenderPositionComponent.h"
#include "../../Components/MovementInterpolatorComponent.h"

#pragma region Classes & Structs

class EntityRegistry;
class ActorFlags;
class ActorLocation;
class ActorDamageSource;
class NewInteractionModel;
class InputMode;
class UIProfanityContext;
class ActorUniqueID;
class ActorDamageCause;
class ItemStack;
class ActorEvent;
class ArmorSlot;
class EquipmentSlot;
class DataLoadHelper;
class ActorLink;
class LevelSoundEvent;
class AnimationComponent;
class RenderParams;
class HandSlot;
class EquipmentTableDefinition;
class Options;
class ActorInteraction;
class ItemStackBase;
class MobEffectInstance;
class Attribute;
class AnimationComponentGroupType;
class ItemUseMethod;
class ResolvedTextObject;
class INpcDialogueData;
class IConstBlockSource;
class ChalkboardBlockPlayer;
class BlockPlayer;
class Block;
class Tick;
class ChunkSource;
class LayeredAbilities;
class ChunkPos;
class MovementEventType;
class PlayerMovementSettings;
class Item;
class Container;
class EventPacket;
class GameType;

class ActorInitializationMethod;
class InitializationMethod;
class VariantParameterList;

class ChalkboardBlockActor;
class ResolvedTextObject;
struct TextObjectRoot;
class SubChunkPos;
class ChunkSource;
class LayeredAbilities;

class ContainerContentChangeListener;
class ItemStack;

// packets
class ChangeDimensionPacket;

#pragma endregion

struct EntityId final { // EntityID for entt
	using EntityType = std::uint32_t;
	static constexpr auto null = entt::null;

	constexpr EntityId(EntityType value = null) noexcept
		: entt{ value } {}

	~EntityId() noexcept = default;

	constexpr EntityId(const EntityId& other) = default;
	constexpr EntityId(EntityId&& other) noexcept = default;

	constexpr EntityId& operator=(const EntityId& other) = default;
	constexpr EntityId& operator=(EntityId&& other) noexcept = default;

	constexpr operator EntityType() const noexcept {
		return entt;
	}

private:
	EntityType entt;
};

class EntityContext { // EntityContext to register Components
public:
	EntityRegistry* mRegistry;
	entt::basic_registry<EntityId>* registry;
	EntityId id{};

	template<typename T>
	T* getComponent() { // getComponent using entt
		auto tryget = const_cast<T*>(registry->try_get<T>(id));
		if (tryget) {
			return tryget;
		}
		return nullptr;
	}
};

// Actor VTable
class Actor { // 1.20.71
public:
	virtual void Destructor(); // ~Actor(); // Actor Destructor
public:
	virtual void getStatusFlag(ActorFlags);
	virtual void setStatusFlag(ActorFlags, bool);
	virtual void outOfWorld(void);
	virtual void reloadHardcoded(ActorInitializationMethod, VariantParameterList const&);
	virtual void reloadHardcodedClient(ActorInitializationMethod, VariantParameterList const&);
	virtual void initializeComponents(ActorInitializationMethod, VariantParameterList const&);
	virtual void reloadComponents(ActorInitializationMethod, VariantParameterList const&);
	virtual void _serverInitItemStackIds(void);
	virtual void _doInitialMove(void);
	virtual bool hasComponent(); // HashedString const&
	//virtual ~Actor(); // virtual void ~Actor();
	virtual void resetUserPos(bool);
	virtual void getOwnerEntityType(void);
	virtual void remove(void);
	virtual bool isRuntimePredictedMovementEnabled(void);
	virtual void getFiringPos(void);
	virtual void getInterpolatedBodyRot(float);
	virtual void getInterpolatedHeadRot(float);
	virtual void getInterpolatedBodyYaw(float);
	virtual void getYawSpeedInDegreesPerSecond(void);
	virtual void getInterpolatedRidingOffset(float, int);
	virtual void resetInterpolated(void);
	virtual bool isFireImmune(void);
	virtual void blockedByShield(ActorDamageSource const&, Actor&);
	virtual bool canDisableShield(void);
	virtual void teleportTo(Vector3<float> const&, bool, int, int, bool);
	virtual void lerpMotion(Vector3<float> const&);
	virtual void tryCreateAddActorPacket(void);
	virtual void normalTick(void);
	virtual void baseTick(void);
	virtual void passengerTick(void);
	virtual void startRiding(Actor&);
	virtual void addPassenger(Actor&);
	virtual void getExitTip(std::string const&, InputMode, NewInteractionModel);
	virtual void getEntityLocNameString(void);
	virtual bool isInWall(void);
	virtual bool isInvisible(void);
	virtual bool canShowNameTag(void);
	virtual std::string getFormattedNameTag(void);
	virtual void getNameTagTextColor(void);
	virtual void getShadowRadius(void);
	virtual void getHeadLookVector(float);
	virtual bool canInteractWithOtherEntitiesInGame(void);
	virtual void getBrightness(float, IConstBlockSource const&);
	virtual void playerTouch(); // Player&
	virtual bool isImmobile(void);
	virtual bool isSilentObserver(void);
	virtual bool isPickable(void);
	virtual bool isSleeping(void);
	virtual void setSleeping(bool);
	virtual void setSneaking(bool);
	virtual bool isBlocking(void);
	virtual bool isDamageBlocked(ActorDamageSource const&);
	virtual bool isAlive(void);
	virtual bool isOnFire(void);
	virtual bool isSurfaceMob(void);
	virtual bool isTargetable(void);
	virtual bool isLocalPlayer(void);
	virtual bool isPlayer(void);
	virtual bool canAttack(Actor*, bool);
	virtual void setTarget(Actor*);
	virtual bool isValidTarget(Actor*);
	virtual void attack(Actor&, ActorDamageCause const&);
	virtual void performRangedAttack(Actor&, float);
	virtual void setOwner(ActorUniqueID);
	virtual void setSitting(bool);
	virtual void onTame(void);
	virtual void onFailedTame(void);
	virtual void setStanding(bool);
	virtual bool canPowerJump(void);
	virtual bool isEnchanted(void);
	virtual void shouldRender(void);
	virtual void playAmbientSound(void);
	virtual void getAmbientSound(void);
	virtual bool isInvulnerableTo(ActorDamageSource const&);
	virtual void getBlockDamageCause(Block const&);
	virtual void doFireHurt(int);
	virtual void onLightningHit(void);
	virtual void feed(int);
	virtual void handleEntityEvent(ActorEvent, int);
	virtual void getPickRadius(void);
	virtual void getActorRendererId(void);
	virtual void despawn(void);
	virtual void setArmor(ArmorSlot, ItemStack const&);
	virtual void getArmorMaterialTypeInSlot(ArmorSlot);
	virtual void getArmorMaterialTextureTypeInSlot(ArmorSlot);
	virtual void getArmorColorInSlot(ArmorSlot, int);
	virtual void setEquippedSlot(int, ItemStack const&);
	virtual void setCarriedItem(ItemStack const&);
	virtual void getCarriedItem(void);
	virtual void setOffhandSlot(ItemStack const&);
	virtual void getEquippedTotem(void);
	virtual void consumeTotem(void);
	virtual void save(CompoundTag&);
	virtual void load(CompoundTag const&, DataLoadHelper&);
	virtual void queryEntityRenderer(void);
	virtual void getSourceUniqueID(void);
	virtual bool canFreeze(void);
	virtual void getLiquidAABB(MaterialType);
	virtual void handleInsidePortal(Vector3<int> const&);
	virtual bool canChangeDimensionsUsingPortal(void);
	virtual void changeDimension(int, int);
	virtual void changeDimension(ChangeDimensionPacket const&);
	virtual void getControllingPlayer(void);
	virtual void causeFallDamageToActor(float, float, ActorDamageSource);
	virtual void onSynchedDataUpdate(int);
	virtual bool canAddPassenger(Actor&);
	virtual bool canPickupItem(ItemStack const&);
	virtual bool canBePulledIntoVehicle(void);
	virtual void inCaravan(void);
	virtual void sendMotionPacketIfNeeded(PlayerMovementSettings const&);
	virtual bool canSynchronizeNewEntity(void);
	virtual void startSwimming(void);
	virtual void stopSwimming(void);
	virtual void buildDebugInfo(std::string&);
	virtual void getCommandPermissionLevel(void);
	virtual void getDeathTime(void);
	virtual bool canBeAffected(int);
	virtual bool canBeAffectedByArrow(MobEffectInstance const&);
	virtual void onEffectRemoved(MobEffectInstance&);
	virtual bool canObstructSpawningAndBlockPlacement(void);
	virtual void getAnimationComponent(void);
	virtual void openContainerComponent(); // Player&
	virtual void swing(void);
	virtual void useItem(ItemStackBase&, ItemUseMethod, bool);
	virtual void getDebugText(std::vector<std::string>&);
	virtual void getMapDecorationRotation(void);
	virtual void getPassengerYRotation(Actor const&);
	virtual void add(ItemStack&);
	virtual void drop(ItemStack const&, bool);
	virtual void getInteraction();
	virtual bool canDestroyBlock(Block const&);
	virtual void setAuxValue(int);
	virtual void startSpinAttack(void);
	virtual void stopSpinAttack(void);
	virtual void renderDebugServerState(Options const&);
	virtual void kill(void);
	virtual void die(ActorDamageSource const&);
	virtual void shouldDropDeathLoot(void);
	virtual void applySnapshot(EntityContext const&, EntityContext const&);
	virtual void getNextStep(float);
	virtual void onPush(Actor&);
	virtual void getLastDeathPos(void);
	virtual void getLastDeathDimension(void);
	virtual bool hasDiedBefore(void);
	virtual void doEnterWaterSplashEffect(void);
	virtual void doExitWaterSplashEffect(void);
	virtual void doWaterSplashEffect(void);
	virtual void _shouldProvideFeedbackOnHandContainerItemSet(int, ItemStack const&);
	virtual void _shouldProvideFeedbackOnArmorSet(ArmorSlot, ItemStack const&);
	virtual void updateEntitySpecificMolangVariables(RenderParams&);
	virtual void shouldTryMakeStepSound(void);
	virtual void _hurt(ActorDamageSource const&, float, bool, bool);
	virtual void readAdditionalSaveData(CompoundTag const&, DataLoadHelper&);
	virtual void addAdditionalSaveData(CompoundTag&);
	virtual void _playStepSound(Vector3<int> const&, Block const&);
	virtual void _doAutoAttackOnTouch(Actor&);
public:
	bool isOnGround() {
		//return EntityContext.getComponent<FlagComponent<OnGroundFlag>>();
		return false;
	}

	PlayerInventory* getSupplies() {
		uintptr_t address = reinterpret_cast<uintptr_t>(this);
		return *reinterpret_cast<PlayerInventory**>(address + 0x7B0);
	}

	std::string* getNametag() {
		void* signature = Utils::findSig("48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 3B 48 8B 08 BA ? ? ? ? 48 8B 40 ? 48 2B C1 48 C1 F8 ? 66 3B D0 73 17");

		auto getNameTag = reinterpret_cast<std::string*(__thiscall*)(Actor*)>(signature); // NameTags signature address
		return getNameTag(this); // Return FunctionCall as Actor
	}

	Vector3<float> getRenderPos() { // getRenderPosition Inside RenderPositionComponent
		auto component = EntityContext.getComponent<RenderPositionComponent>(); // get the Component using entt
		if (component != nullptr) { return component->renderPos; } // If the component isn't nullptr return the Vector3
		return { 0, 0, 0 }; // If component is nullptr return 0, 0, 0 for Render Position
	}

	ActorCollision* getActorCollision() {
		return (ActorCollision*)((uintptr_t)this + 8);
	}
public:
	// EntityContext
	BUILD_ACCESS(class EntityContext, EntityContext, 0x8); // 1.20.71
	// Level Actor::getLevel(void)
	BUILD_ACCESS(class Level*, Level, 0x258); // 1.20.71
	// StateVectorComponent Actor::getPosition(void)
	BUILD_ACCESS(StateVectorComponent*, StateVector, 0x298); // 1.20.71
	// AABBShapeComponent Actor::getAABB(void) or StateVector + 8
	BUILD_ACCESS(AABBShapeComponent*, AABBShape, 0x2A0); // 1.20.71
	// MovementInterpolatorComponent Actor::getRotation(void) or StateVector + 16
	BUILD_ACCESS(MovementInterpolatorComponent*, MovementInterpolator, 0x2A8); // 1.20.71
};