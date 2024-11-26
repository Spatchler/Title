#include "baseNode.hpp"

Title::BaseNode::BaseNode() {}

void Title::BaseNode::drawTree() {
  this->drawNode();
  drawChildren();
}

void Title::BaseNode::updateTree() {
  this->updateNode();
  updateChildren();
}

void Title::BaseNode::drawChildren() {
  for (BaseNode* c: mChildren) {
    if (c->visible)
      c->draw();
  }
}

void Title::BaseNode::updateChildren() {
  for (BaseNode* c: mChildren) {
    c->update();
  }
}

void Title::BaseNode::attach(BaseNode* pNode) {
  pNode->setParentNode(this);
  mChildren.push_back(pNode);
  pNode->setNodeID(mChildren.size() - 1);
}

void Title::BaseNode::detach(uint pNodeID) {
  mChildren.erase(mChildren.begin() + pNodeID);
  for (uint i = pNodeID; i < mChildren.size() - 1; ++i) {
    mChildren.at(i)->setNodeID(i);
  }
}

void Title::BaseNode::setParentNode(BaseNode* pNode) {
  mParentNode = pNode;
}

void Title::BaseNode::setParentScene(Scene* pScene) {
  mParentScene = pScene;
  for (BaseNode* c: mChildren) {
    c->setParentScene(pScene);
  }
}

void Title::BaseNode::setNodeID(uint pNodeID) {
  mNodeID = pNodeID;
}

void Title::BaseNode::getNodeID() {
  return mNodeID;
}
