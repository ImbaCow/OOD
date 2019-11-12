#pragma once
#include "ILineStyle.h"

class CLineStyleGroup : public ILineStyle
{
public:
	CLineStyleGroup(const std::vector<std::shared_ptr<ILineStyle>>& styleArr);

	virtual std::optional<bool> IsEnabled() const override;
	virtual void Enable(bool enable) override;

	virtual std::optional<RGBAColor> GetColor() const override;
	virtual void SetColor(RGBAColor color) override;

	virtual std::optional<double> GetLineSize() const override;
	virtual void SetLineSize(double lineSize) override;

private:
	std::vector<std::shared_ptr<ILineStyle>> m_styleArr;
};
