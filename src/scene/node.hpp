#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "../mesh/static_mesh.hpp"
#include "../mesh/animated_mesh.hpp"

class C_Node
{
    public:
        C_Node(const std::string);
        ~C_Node();
        void Draw(const bool);
        void DrawWithPicking();
        void Timer();

        const std::string& GetNodeName() const;
        C_Node *_next;

        void AddStaticMesh(C_Static_Mesh*);
        void AddAnimatedMesh(C_Animated_Mesh*);
        C_Static_Mesh* GetStaticMesh(const int);
        C_Animated_Mesh* GetAnimatedMesh(const int);

        void Translate(float, float, float);
        void TranslateX(float);
        void TranslateY(float);
        void TranslateZ(float);
        void Rotate(float, float, float);
        void RotateX(float);
        void RotateY(float);
        void RotateZ(float);
        void Scale(float, float, float);
        void ScaleX(float);
        void ScaleY(float);
        void ScaleZ(float);
        void CallTransformation(const bool);
    protected:
        std::string _name;

        C_Static_Mesh *_static_mesh;
        void DeleteStaticMeshes(C_Static_Mesh*);
        C_Animated_Mesh *_animated_mesh;
        void DeleteAnimatedMeshes(C_Animated_Mesh*);

        Vector3D _translation;
        Vector3D _rotation;
        Vector3D _scale;
};

#endif // NODE_HPP_INCLUDED
