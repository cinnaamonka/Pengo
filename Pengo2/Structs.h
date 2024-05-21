#pragma once
#include <unordered_map>
#include <string>

enum class PengoSounds
{
	Background,
	BlockPushed,
	IceBlockDestroyed,
	PlayerDeath,
	ActStarts,
	DiamondBlocksLinedUp,
	SnoBeeEggDestroyed,
	SnowBeeSpawning,
	SnowBeeSquashed,
	MaxSounds

};
enum class BlocksTypes
{
	Diamond,
	Eggs,
	VerBorder,
	HorBorder,
	BreaksOnSpot,
	Breakable

};
const std::unordered_map<PengoSounds, std::string> SOUND_PATH_MAPPING
{

	{ PengoSounds::Background, "../Data/Sound/Background.mp3" },
	{ PengoSounds::BlockPushed, "../Data/Sound/PushedBlock.mp3" },
	{ PengoSounds::IceBlockDestroyed, "../Data/Sound/IceBlockDestroyed.mp3" },
	{ PengoSounds::PlayerDeath, "../Data/Sound/PlayerDied.mp3" },
	{ PengoSounds::ActStarts, "../Data/Sound/ActStart.mp3" },
	{ PengoSounds::DiamondBlocksLinedUp, "../Data/Sound/DiamondBlocksLinedUp.mp3" },
	{ PengoSounds::SnoBeeEggDestroyed, "../Data/Sound/SnowBeeEggDestroyed.mp3" },
	{ PengoSounds::SnowBeeSpawning, "../Data/Sound/SnowBeeSpawning.mp3" },
	{ PengoSounds::SnowBeeSquashed, "../Data/Sound/SnowBeeSquashed.mp3" }

};
