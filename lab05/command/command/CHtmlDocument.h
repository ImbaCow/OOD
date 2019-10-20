#pragma once
#include "pch.h"
#include "IDocument.h"
#include "CCommandHistory.h"

class CHtmlDocument : public IDocument
{
public:
	virtual ~CHtmlDocument() = default;

	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, std::optional<size_t> position = std::nullopt) override;
	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height, std::optional<size_t> position = std::nullopt) override;

	virtual size_t GetItemsCount() const override;

	virtual CConstDocumentItem GetItem(size_t index) const override;
	virtual CDocumentItem GetItem(size_t index) override;
	virtual void DeleteItem(size_t index) override;

	virtual std::string GetTitle() const override;
	virtual void SetTitle(const std::string& title) override;

	virtual void Save(const Path& path) const override;

	virtual bool CanUndo() const override;
	virtual bool CanRedo() const override;

	virtual void Undo() override;
	virtual void Redo() override;

private:
	std::string m_title;
	std::vector<CDocumentItem> m_documentItemArr;
	CCommandHistory m_history;
};
