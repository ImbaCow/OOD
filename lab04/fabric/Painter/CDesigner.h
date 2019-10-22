#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"

class CDesigner : public IDesigner
{
public:
	CDesigner(std::shared_ptr<IShapeFactory> factory);
	virtual ~CDesigner() = default;

	virtual CPictureDraft CreateDraft(std::istream& stream) override;

private:
	std::shared_ptr<IShapeFactory> m_factory;
};
