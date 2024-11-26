#pragma once

#include <vector>

namespace Title {
  class BaseNode {
  public:
    BaseNode() {}

    // draw/update this node then its children
    void drawTree();
    void updateTree();

    // draw/update just this node - different for different nodes
    virtual void drawNode() {}
    virtual void updateNode() {}

    void drawChildren();
    void updateChildren();

    void attach(BaseNode* pNode);
    void detach(uint pNodeID);

    void setParentNode(BaseNode* pNode);
    void setParentScene(Scene* pScene);

    void setNodeID(uint pNodeID);
    void getNodeID();
  private:
    uint mNodeID;
    BaseNode* mParentNode = nullptr;
    Scene* mParentScene = nullptr;
    std::vector<BaseNode*> mChildren;
  };
}
