#pragma once

#include "..\Templates\ProtogenProjectTemplate.h"
#include "..\..\Assets\Models\FBX\MatthewFace.h"

#include "..\..\Camera\CameraManager\Implementations\WS35SplitCameras.h"
#include "..\..\Controller\WS35Controller.h"

#include "..\..\Assets\Textures\Animated\Spiral.h"
#include "..\..\Assets\Textures\Static\Angle.h"
#include "..\..\Assets\Textures\Static\Heart.h"

class MatthewProtoProject : public ProtogenProject {
private:
    WS35SplitCameraManager cameras;
    WS35Controller controller = WS35Controller(&cameras, 50);
    MatthewFace pM;
    
	const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("ANGRY"), F("DOUBT"), F("FROWN"), F("LOOKUP"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    MaterialAnimator<7> backgroundMaterial;

    SpiralSequence spiral = SpiralSequence(Vector2D(60.0f,60.0f),Vector2D(125.0f,75.0f),24);
    Heart heart = Heart(Vector2D(50, 50),Vector2D(125,75));
    Angle angle = Angle(Vector2D(-60, 50),Vector2D(125,75));

    void LinkControlParameters() override {
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Anger), MatthewFace::Anger, 15, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Sadness), MatthewFace::Sadness, 50, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Surprised), MatthewFace::Surprised, 10, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Doubt), MatthewFace::Doubt, 25, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Frown), MatthewFace::Frown, 45, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::LookUp), MatthewFace::LookUp, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::LookDown), MatthewFace::LookDown, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::Angle), MatthewFace::Angle, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::HideEye), MatthewFace::HideEye, 30, 0.0f, 1.0f);
        eEA.AddParameter(pM.GetMorphWeightReference(MatthewFace::HideBlush), MatthewFace::HideBlush, 30, 1.0f, 0.0f);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(MatthewFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(MatthewFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(MatthewFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(MatthewFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(MatthewFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(MatthewFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(MatthewFace::vrc_v_ss));

        eEA.AddParameter(&offsetFace, offsetFaceInd, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceSA, offsetFaceIndSA, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceARG, offsetFaceIndARG, 40, 0.0f, 1.0f);
        eEA.AddParameter(&offsetFaceOSC, offsetFaceIndOSC, 40, 0.0f, 1.0f);

        blink.AddParameter(pM.GetMorphWeightReference(MatthewFace::Blink));
    }

    void SetMaterialLayers() {
        materialAnimator.SetBaseMaterial(Material::Add, &gradientMat);
        materialAnimator.AddMaterial(Material::Replace, &orangeMaterial, 40, 0.0f, 1.0f);//layer 1
        materialAnimator.AddMaterial(Material::Replace, &whiteMaterial, 40, 0.0f, 1.0f);//layer 2
        materialAnimator.AddMaterial(Material::Replace, &greenMaterial, 40, 0.0f, 1.0f);//layer 3
        materialAnimator.AddMaterial(Material::Replace, &yellowMaterial, 40, 0.0f, 1.0f);//layer 4
        materialAnimator.AddMaterial(Material::Replace, &purpleMaterial, 40, 0.0f, 1.0f);//layer 5
        materialAnimator.AddMaterial(Material::Replace, &redMaterial, 40, 0.0f, 1.0f);//layer 6
        materialAnimator.AddMaterial(Material::Replace, &blueMaterial, 40, 0.0f, 1.0f);//layer 7
        materialAnimator.AddMaterial(Material::Replace, &rainbowSpiral, 40, 0.0f, 1.0f);//layer 8

        backgroundMaterial.SetBaseMaterial(Material::Add, Menu::GetMaterial());
        backgroundMaterial.AddMaterial(Material::Add, &sA, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &aRG, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &oSC, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &spiral, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &heart, 20, 0.0f, 1.0f);
        backgroundMaterial.AddMaterial(Material::Add, &angle, 20, 0.0f, 1.0f);
    }

    void Default(){}

    void Angry(){
        eEA.AddParameterFrame(MatthewFace::Anger, 1.0f);
    } 

    void Sad(){
        eEA.AddParameterFrame(MatthewFace::Sadness, 1.0f);
        eEA.AddParameterFrame(MatthewFace::Frown, 1.0f);
    }

    void Surprised(){
        eEA.AddParameterFrame(MatthewFace::Angle, 1.0f);
        eEA.AddParameterFrame(MatthewFace::HideBlush, 0.0f);
        blinkSet = false;
    }
    
    void Doubt(){
        eEA.AddParameterFrame(MatthewFace::Doubt, 1.0f);
    }
    
    void Frown(){
        eEA.AddParameterFrame(MatthewFace::Frown, 1.0f);
    }

    void LookUp(){
        eEA.AddParameterFrame(MatthewFace::LookUp, 1.0f);
    }

    void LookDown(){
        eEA.AddParameterFrame(MatthewFace::LookDown, 1.0f);
    }

    void SpiralEyes(){
        eEA.AddParameterFrame(MatthewFace::HideEye, 1.0f);
        backgroundMaterial.AddMaterialFrame(spiral, 1.0f);
        spiral.Update();
        blinkSet = false;
    }

    void HeartEyes(){
        eEA.AddParameterFrame(MatthewFace::HideEye, 1.0f);
        backgroundMaterial.AddMaterialFrame(heart, 1.0f);
        blinkSet = false;
    }

    void AngleEyes(){
        eEA.AddParameterFrame(MatthewFace::HideEye, 1.0f);
        backgroundMaterial.AddMaterialFrame(angle, 1.0f);
        blinkSet = false;
    }

public:
    MatthewProtoProject() : ProtogenProject(&cameras, &controller, 1, Vector2D(), Vector2D(192.0f, 105.0f), 22, 0, 9){
        scene.AddObject(pM.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());

        whiteMaterial = SimpleMaterial(RGBColor(255, 255, 150));

        background.GetObject()->SetMaterial(&backgroundMaterial);

        LinkControlParameters();
        SetMaterialLayers();

        hud.SetFaceArray(faceArray);
    }

    void Update(float ratio) override {
        pM.Reset();

        uint8_t mode = Menu::GetFaceState();//change by button press

        if (isBooped && mode < 6){
            Surprised();
        }
        else{
            if (mode == 0) Default();
            else if (mode == 1) Angry();
            else if (mode == 2) Doubt();
            else if (mode == 3) Frown();
            else if (mode == 4) LookUp();
            else if (mode == 5) Sad();
            else if (mode == 6) SpiralEyes();
            else if (mode == 7) HeartEyes();
            else if (mode == 8) AngleEyes();
            else {
                Default();
                blinkSet = false;
            }
        }

        if (blinkSet) {
            EnableBlinking();
        } else {
            DisableBlinking();
        }

        UpdateFace(ratio);

        backgroundMaterial.Update();

        pM.SetMorphWeight(MatthewFace::BiggerNose, 1.0f);
        pM.SetMorphWeight(MatthewFace::MoveEye, 1.0f);

        pM.Update();

        AlignObjectFace(pM.GetObject(), -7.5f);

        SetWiggleSpeed(0.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(2.5f, -3.0f));
        SetMenuSize(Vector2D(240, 64));
        
        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }
};
