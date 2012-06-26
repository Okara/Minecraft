#ifndef CINEMATIC_HPP_INCLUDED
#define CINEMATIC_HPP_INCLUDED

#include "cube.hpp"
#include "chunk.hpp"
#include "..\tools\mod.hpp"

class C_Game : public C_Mod, sf::Thread
{
    public:
        C_Game(sf::RenderWindow*);
        ~C_Game();
    protected:
        virtual void MousePressed();
        virtual void MouseReleased();
        virtual void MouseMoved();
        virtual void KeyPressed();
        virtual void KeyReleased();
        virtual void MouseWheel();
        virtual void Draw();
        virtual void TimerManagement();

        virtual void Run();

        void Picking();
        void LeftClick();
        void RightClick();

        GLuint _texture;
        void InitTexture();

        int _fogStart;
        void InitFog();

        C_Cube *_cube;
        Vector3D _vSelectedCube;
        bool _bSelectedCube;
        void InitCubes();
        void DrawCube(const int);
        const unsigned char GetCubeType(const int, const int, const int);
        void DeleteCubeOfVector(const int, const int, const int, const int);
        void CheckCubeVisibility(const int, const int, const int);

        C_Cube _cubeBreakAnim[10];
        short _frameBreakAnim;
        sf::Clock _timerBreakAnim;
        bool _boolBreakAnim;

        int _actualChunkX, _actualChunkY;
        std::vector<MinecraftChunk*> _chunks;
        void CreateRandomChunk(const int, const int);
        void DeleteChunkFromMemory(const int, const int);
        MinecraftChunk* GetChunk(const int, const int);
        void CheckChunksCubesVisibility(const int, const int);
        void SaveChunk(const int, const int);
        const bool LoadChunk(const int, const int);

        sf::Clock _timerPhysics;
        bool _boolJumping, _isFalling;
        int _frameJumping;
        void CallPhysicsFunctions();


        unsigned char _actuelCubeInHand;
        std::vector<tabCube> _tabCube[NB_TYPE_CUBE];

        sf::Sprite _sprHotkeys;
        sf::Sprite _sprSelectedHotkeys;
        unsigned char _itemInHotkeys[9];
        sf::Sprite _sprItemInHotkeys[9];
        int _actualHotkeys;
        //unsigned char _itemInDragAndDrop;
        //unsigned char _itemInInventory[27];

        void InitGUI();
        void SetItemInHotkeys(const unsigned char, const int);
};

#endif // CINEMATIC_HPP_INCLUDED
