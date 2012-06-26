#include "node.hpp"

C_Node::C_Node(const std::string str)
{
    _name = str;

    _static_mesh = NULL;
    _animated_mesh = NULL;

    _next = NULL;

    _scale = Vector3D(1.0f, 1.0f, 1.0f);

    C_Log::GetSingleton()->AddMessage("Node "+_name+" created.");
}

C_Node::~C_Node()
{
    if(_static_mesh != NULL)
        DeleteStaticMeshes(_static_mesh);

    if(_animated_mesh != NULL)
        DeleteAnimatedMeshes(_animated_mesh);

    C_Log::GetSingleton()->AddMessage("Node "+_name+" deleted.");
}

const std::string& C_Node::GetNodeName() const
{
    return _name;
}

void C_Node::Draw(const bool bo)
{
    glPushMatrix();
    {
        CallTransformation(bo);

        C_Static_Mesh *parc = _static_mesh;
        while(parc != NULL)
        {
            parc->Draw();
            parc = parc->_next;
        }

        C_Animated_Mesh *parco = _animated_mesh;
        while(parco != NULL)
        {
            parco->Draw();
            parco = parco->_next;
        }
    }
    glPopMatrix();
}

void C_Node::DrawWithPicking()
{
    glPushMatrix();

    CallTransformation(true);

    C_Static_Mesh *parc = _static_mesh;
    GLuint i=0;
    glPushName(0);
    while(parc != NULL)
    {
        glPushName(i);
        parc->Draw();
        glPopName();
        parc = parc->_next;
        i++;
    }
    glPopName();

    C_Animated_Mesh *parco = _animated_mesh;
    i = 0;
    glPushName(1);
    while(parco != NULL)
    {
        glPushName(i);
        parco->Draw();
        glPopName();
        parco = parco->_next;
        i++;
    }
    glPopName();

    glPopMatrix();
}

C_Static_Mesh* C_Node::GetStaticMesh(const int me)
{
    C_Static_Mesh *mesh = _static_mesh;
    for(int i=0;i<me;i++)
        mesh = mesh->_next;

    return mesh;
}

C_Animated_Mesh* C_Node::GetAnimatedMesh(const int me)
{
    C_Animated_Mesh *mesh = _animated_mesh;
    for(int i=0;i<me;i++)
        mesh = mesh->_next;

    return mesh;
}

void C_Node::AddStaticMesh(C_Static_Mesh *me)
{
    if(_static_mesh == NULL)
        _static_mesh = me;
    else
    {
        C_Static_Mesh *parc = _static_mesh;
        while(parc->_next != NULL)
        {
            parc = parc->_next;
        }
        parc->_next = me;
    }
}

void C_Node::DeleteStaticMeshes(C_Static_Mesh *me)
{
    if(me != NULL)
    {
        if(me->_next != NULL)
            DeleteStaticMeshes(me->_next);
        delete me;
        me = NULL;
    }
}

void C_Node::AddAnimatedMesh(C_Animated_Mesh *me)
{
    if(_animated_mesh == NULL)
        _animated_mesh = me;
    else
    {
        C_Animated_Mesh *parc = _animated_mesh;
        while(parc->_next != NULL)
        {
            parc = parc->_next;
        }
        parc->_next = me;
    }
}

void C_Node::DeleteAnimatedMeshes(C_Animated_Mesh *me)
{
    if(me != NULL)
    {
        if(me->_next != NULL)
            DeleteAnimatedMeshes(me->_next);
        delete me;
        me = NULL;
    }
}

void C_Node::Timer()
{
    C_Animated_Mesh *parco = _animated_mesh;
    while(parco != NULL)
    {
        parco->Movement();
        parco = parco->_next;
    }
}

void C_Node::Translate(float x, float y, float z)
{
    _translation = Vector3D(x, y, z);
}

void C_Node::TranslateX(float x)
{
    _translation.X = x;
}

void C_Node::TranslateY(float y)
{
    _translation.Y = y;
}

void C_Node::TranslateZ(float z)
{
    _translation.Z = z;
}

void C_Node::Rotate(float x, float y, float z)
{
    _rotation = Vector3D(x, y, z);
}

void C_Node::RotateX(float x)
{
    _rotation.X = x;
}

void C_Node::RotateY(float y)
{
    _rotation.Y = y;
}

void C_Node::RotateZ(float z)
{
    _rotation.Z = z;
}

void C_Node::Scale(float x, float y, float z)
{
    _scale = Vector3D(x, y, z);
}

void C_Node::ScaleX(float x)
{
    _scale.X = x;
}

void C_Node::ScaleY(float y)
{
    _scale.Y = y;
}

void C_Node::ScaleZ(float z)
{
    _scale.Z = z;
}

void C_Node::CallTransformation(const bool bo)
{
    if(bo)
        glScalef(_scale.X, _scale.Y, _scale.Z);
    else
        glScalef(_scale.X, _scale.Y, -_scale.Z);

    glRotatef(_rotation.X, 1.0f, 0.0f, 0.0f);
    glRotatef(_rotation.Y, 0.0f, 0.0f, 1.0f);
    glRotatef(_rotation.Z, 0.0f, 1.0f, 0.0f);

    glTranslatef(_translation.X, _translation.Y, _translation.Z);
}
