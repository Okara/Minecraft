#include "scenemanager.hpp"

void DrawWater()
{
    glColor4f(0, 0, 0, 0.5f);
    glBegin(GL_TRIANGLES);
        glVertex3f(2000, 2000, 0);
        glVertex3f(-2000, 2000, 0);
        glVertex3f(-2000, -2000, 0);

        glVertex3f(2000, 2000, 0);
        glVertex3f(-2000, -2000, 0);
        glVertex3f(2000, -2000, 0);
    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

C_SceneManager::C_SceneManager()
{
    _light = NULL;

    _node = NULL;

    nodeGround = new C_Node("node_carrelage");
    {C_Animated_Mesh *entity = new C_Animated_Mesh("carrelage");
    entity->SetMesh("data/mesh/carrelage");
    nodeGround->AddAnimatedMesh(entity);}
    nodeGround->Scale(25, 25, 25);
    nodeGround->TranslateZ(-0.001f);
}

C_SceneManager::~C_SceneManager()
{
    C_Resource::GetSingleton()->clear();

    DeleteLights(_light);
    DeleteNodes(_node);

    delete nodeGround;
}

void C_SceneManager::Draw()
{
    glLightfv(GL_LIGHT0, GL_POSITION, _light->_pos);

    glPushMatrix();

    glDisable( GL_CULL_FACE );
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
        DrawWater();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    glStencilFunc(GL_EQUAL, 1, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glEnable(GL_CLIP_PLANE0);
    double equ0[] = { 0.0f, 0.0f, -1.0f, 0.0f } ;
    glClipPlane(GL_CLIP_PLANE0,equ0);

    glDisable(GL_DEPTH_TEST);
    nodeGround->Draw(true);
    glEnable(GL_DEPTH_TEST);

    {C_Node *parc = _node;
    while(parc != NULL)
    {
        parc->Draw(false);
        parc = parc->_next;
    }}

    glDisable(GL_CLIP_PLANE0);

    glDisable(GL_STENCIL_TEST);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        DrawWater();
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable( GL_CULL_FACE );

    {C_Node *parc = _node;
    while(parc != NULL)
    {
        parc->Draw(true);
        parc = parc->_next;
    }}
}

void C_SceneManager::AddLight(C_Light *li)
{
    if(_light == NULL)
        _light = li;
    else
    {
        C_Light *parc = _light;
        while(parc->_next != NULL)
        {
            parc = parc->_next;
        }
        parc->_next = li;
    }
}

void C_SceneManager::DeleteLights(C_Light *li)
{
    if(li->_next != NULL)
        DeleteLights(li->_next);
    delete li;
}

void C_SceneManager::AddNode(C_Node *no)
{
    if(_node == NULL)
        _node = no;
    else
    {
        C_Node *parc = _node;
        while(parc->_next != NULL)
        {
            parc = parc->_next;
        }
        parc->_next = no;
    }
}

void C_SceneManager::DeleteNodes(C_Node *no)
{
    if(no->_next != NULL)
        DeleteNodes(no->_next);
    delete no;
}

C_Node* C_SceneManager::GetNode(const std::string str)
{
    C_Node *parco = _node;
    while(parco != NULL)
    {
        if(parco->GetNodeName() == str)
            return parco;
        parco = parco->_next;
    }

    return NULL;
}

void C_SceneManager::Timer()
{
    C_Node *parco = _node;
    while(parco != NULL)
    {
        parco->Timer();
        parco = parco->_next;
    }
}

void C_SceneManager::Picking(const float cursorX, const float cursorY)
{
    GLuint selectBuf[512];

    GLint viewport[4];

	glSelectBuffer(512,selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(cursorX,viewport[3]-cursorY,
			5,5,viewport);
	gluPerspective(90, (900.0f / 670.0f) ,0.1,10000);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();

	C_Node *parc = _node;
	GLuint i = 0;
    while(parc != NULL)
    {
        glPushName(i);
        parc->DrawWithPicking();
        glPopName();
        parc = parc->_next;
        i++;
    }

	int hits;
	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);

	// if there are hits process them
	if (hits != 0)
	{
	    unsigned int i, j;
       GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

       printf ("hits = %d\n", hits);
       ptr = (GLuint *) selectBuf;
       minZ = 0xffffffff;
       for (i = 0; i < hits; i++)
       {
            names = *ptr;
            ptr++;
            if (*ptr < minZ)
            {
                numberOfNames = names;
                minZ = *ptr;
                ptrNames = ptr+2;
            }

            ptr += names+2;
        }
        printf ("The closest hit names are ");
        ptr = ptrNames;

        int node, type, mesh;
        for (j = 0; j < numberOfNames; j++,ptr++)
        {
            if(j == 0)
                node = *ptr;
            else if(j == 1)
                type = *ptr;
            else if(j == 2)
                mesh = *ptr;
            else
                std::cout<<"Picking error !"<<std::endl;
        }
        std::cout<<mesh<<" "<<type<<" "<<node<<" z : "<<minZ<<std::endl;

        C_Node *no = _node;
        for(int a=0;a<node;a++)
            no = no->_next;

        if(type == 0)
            std::cout<<"Name => "<<no->GetStaticMesh(mesh)->GetName()<<std::endl;
        else if(type == 1)
            std::cout<<"Name => "<<no->GetAnimatedMesh(mesh)<<std::endl;
        else
            std::cout<<"Picking error : bad type."<<std::endl;
	}
}
