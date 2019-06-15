#include "Sprite.h"

Sprite::Sprite(Tag tag, int left, int top, int right, int bottom)
{
	this->tag = tag;
	_texture = TextureFactory::GetInstance()->GetTexture(tag);
	_rect.top = top;
	_rect.left = left;
	_rect.right = right;
	_rect.bottom = bottom;
	_center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
}
void Sprite::Render(float x, float y, float translateX, float translateY)
{
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(_center.x, _center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pTranslation = D3DXVECTOR2(translateX, translateY);
	auto pScaling = D3DXVECTOR2(isReverse ? -1 : 1, 1);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(_texture, &_rect, &_center, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}