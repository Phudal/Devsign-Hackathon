#include "SpriteAnimInfo.h"

FSpriteAnimInfo::FSpriteAnimInfo()
{
	SpriteDelay = 0.0f;
}

void FSpriteAnimInfo::InitializeSpriteAnimInfo(const vector<FSpriteInfo*> spriteInfos, float spriteDelay)
{
	for (auto spriteInfo : spriteInfos)
		SpriteInfos.push_back(spriteInfo);

	SpriteDelay = spriteDelay;
}

void FSpriteAnimInfo::Release()
{

	for (auto iter = SpriteInfos.begin(); iter != SpriteInfos.end(); ++iter)
		CObject::DeleteObject(*iter);
	SpriteInfos.clear();

	super::Release();
}
