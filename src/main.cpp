#include <Geode/Geode.hpp>

#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	// Replacing the sprite of the delete all StartPos button
	bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer))
			return false;

		NodeIDs::provideFor(this);

		auto deleteCategoryMenu = this->getChildByID("delete-category-menu");

		if (!deleteCategoryMenu)
			return true;

		auto deleteButtonMenu = deleteCategoryMenu->getChildByID("delete-button-menu");
		auto deleteStartPosButton = deleteButtonMenu->getChildByID("delete-startpos-button");
		auto buttonSprite = deleteStartPosButton->getChildByType<ButtonSprite>(0);

		// Getting the sprite that gets replaced by the new one
		CCNode* deleteAllSprite = nullptr;

		auto children = buttonSprite->getChildrenExt();
		for (auto* child : children) {
			if (child->getChildrenCount() > 0) {
				deleteAllSprite = child;
				break;
			}
		}

		if (!deleteAllSprite)
			return true;

		// Removing the old sprite
		auto label = getChildBySpriteFrameName(deleteAllSprite, "GJ_deleteAllIcon_001.png");
		if (!label)
			return true;

		label->removeFromParent();

		// Adding the new sprite
		auto newLabel = CCSprite::create("disableAllIcon.png"_spr);
		deleteAllSprite->addChild(newLabel);
		newLabel->setPosition(label->getPosition());

		return true;
	}

	void onDeleteStartPos(CCObject* sender) {
		auto& editorLayer = this->m_editorLayer;
		CCArrayExt<GameObject*> objects = editorLayer->m_objects;

		if (!editorLayer) return; // I have no idea if this helps with anything, it probably doesn't

		for (auto* object : objects) {
			if (object->m_objectID != 31) continue; // Continue if the object is not a StartPos

			auto startPosObject = static_cast<StartPosObject*>(object);
			auto& disabled = startPosObject->m_startSettings->m_disableStartPos;

			disabled = true;
		}
	}
};