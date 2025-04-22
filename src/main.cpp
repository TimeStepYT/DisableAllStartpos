#include <Geode/Geode.hpp>

#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	// Replacing the sprite of the delete all StartPos button
	bool init(LevelEditorLayer * editorLayer) {
		if (!EditorUI::init(editorLayer))
			return false;

		NodeIDs::provideFor(this);

		auto deleteCategoryMenu = this->getChildByID("delete-category-menu");
		auto deleteButtonMenu = deleteCategoryMenu->getChildByID("delete-button-menu");
		auto deleteStartPosButton = deleteButtonMenu->getChildByID("delete-startpos-button");
		auto buttonSprite = deleteStartPosButton->getChildByType<ButtonSprite>(0);

		// Getting the sprite that gets replaced by the new one
		CCArrayExt<CCSprite*> buttonSpriteArray = buttonSprite->getChildren();
		CCSprite* deleteAllSprite = nullptr;
		for (auto sprite : buttonSpriteArray) {
			if (sprite->getChildrenCount() == 2) {
				deleteAllSprite = sprite;
				break;
			}
		}

		if (!deleteAllSprite)
			return true;

		// Removing the old sprite
		auto label = deleteAllSprite->getChildByType<CCSprite>(0);
		label->removeFromParent();

		// Adding the new sprite
		auto newLabel = CCSprite::create("disableAllIcon.png"_spr);
		deleteAllSprite->addChild(newLabel);
		newLabel->setPosition(label->getPosition());

		return true;
	}

	void onDeleteStartPos(CCObject * sender) {
		auto& editorLayer = this->m_editorLayer;
		CCArrayExt<GameObject*> objects = editorLayer->m_objects;

		if (!editorLayer) return; // I have no idea if this helps with anything

		for (auto object : objects) {
			if (object->m_objectID != 31) continue; // Continue if the object is not a StartPos

			auto startPosObject = static_cast<StartPosObject*>(object);
			auto& disabled = startPosObject->m_startSettings->m_disableStartPos;

			disabled = true;
		}
	}
};