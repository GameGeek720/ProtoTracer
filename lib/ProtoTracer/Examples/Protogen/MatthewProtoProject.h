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
        AddParameter(MatthewFace::Anger, pM.GetMorphWeightReference(MatthewFace::Anger), 15);
        AddParameter(MatthewFace::Sadness, pM.GetMorphWeightReference(MatthewFace::Sadness), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(MatthewFace::Surprised, pM.GetMorphWeightReference(MatthewFace::Surprised), 15);
        AddParameter(MatthewFace::Doubt, pM.GetMorphWeightReference(MatthewFace::Doubt), 15);
        AddParameter(MatthewFace::Frown, pM.GetMorphWeightReference(MatthewFace::Frown), 15);
        AddParameter(MatthewFace::LookUp, pM.GetMorphWeightReference(MatthewFace::LookUp), 15);
        AddParameter(MatthewFace::LookDown, pM.GetMorphWeightReference(MatthewFace::LookDown), 15);
        AddParameter(MatthewFace::Angle, pM.GetMorphWeightReference(MatthewFace::Angle), 15);
        AddParameter(MatthewFace::HideEye, pM.GetMorphWeightReference(MatthewFace::HideEye), 15);

        AddParameter(MatthewFace::HideBlush, pM.GetMorphWeightReference(MatthewFace::HideBlush), 15, IEasyEaseAnimator::InterpolationMethod::Cosine, true);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(MatthewFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(MatthewFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(MatthewFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(MatthewFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(MatthewFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(MatthewFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(MatthewFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(MatthewFace::Blink));
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
        AddParameterFrame(MatthewFace::Anger, 1.0f);
    } 

    void Sad(){
        AddParameterFrame(MatthewFace::Sadness, 1.0f);
        AddParameterFrame(MatthewFace::Frown, 1.0f);
    }

    void Surprised(){
        AddParameterFrame(MatthewFace::Angle, 1.0f);
        AddParameterFrame(MatthewFace::HideBlush, 0.0f);
        blinkSet = false;
    }
    
    void Doubt(){
        AddParameterFrame(MatthewFace::Doubt, 1.0f);
    }
    
    void Frown(){
        AddParameterFrame(MatthewFace::Frown, 1.0f);
    }

    void LookUp(){
        AddParameterFrame(MatthewFace::LookUp, 1.0f);
    }

    void LookDown(){
        AddParameterFrame(MatthewFace::LookDown, 1.0f);
    }

    void SpiralEyes(){
        AddParameterFrame(MatthewFace::HideEye, 1.0f);
        backgroundMaterial.AddMaterialFrame(spiral, 1.0f);
        spiral.Update();
        blinkSet = false;
    }

    void HeartEyes(){
        AddParameterFrame(MatthewFace::HideEye, 1.0f);
        backgroundMaterial.AddMaterialFrame(heart, 1.0f);
        blinkSet = false;
    }

    void AngleEyes(){
        AddParameterFrame(MatthewFace::HideEye, 1.0f);
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
