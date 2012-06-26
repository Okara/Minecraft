#ifndef SCENEMANAGER_HPP_INCLUDED
#define SCENEMANAGER_HPP_INCLUDED

#include "light.hpp"
#include "node.hpp"

class C_SceneManager
{
    public:
        C_SceneManager();
        ~C_SceneManager();

        void Draw();
        void AddLight(C_Light*);

        void AddNode(C_Node*);
        C_Node* GetNode(const std::string);

        void Timer();
        void Picking(const float, const float);
    protected:
        void DeleteLights(C_Light*);
        void DeleteNodes(C_Node*);

        C_Light *_light;

        C_Node *_node;
        C_Node *nodeGround;
};

#endif // SCENEMANAGER_HPP_INCLUDED
