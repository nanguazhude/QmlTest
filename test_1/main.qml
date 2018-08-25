import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Particles 2.11
import QtGraphicalEffects 1.0

Rectangle {

    property int theCounter : 100 ;

    id : _id_root;
    width:  640;
    height: 480;
    border.width: 0;
    z:0;
    color :( function(){ var tmpVar = Math.random()/6.3; return Qt.rgba(0.05+tmpVar ,tmpVar,tmpVar ,1) ;} )()

    RadialGradient {
        anchors.fill: parent ;
        horizontalOffset: 0;
        verticalOffset: 0;
        horizontalRadius: Math.min(parent.width,parent.height)   ;
        verticalRadius:   Math.min(parent.width,parent.height)   ;
        angle: 0;
        gradient: Gradient {
            GradientStop { position: 0.0; color:Qt.rgba(0.153,0.135,0.135,0.85); }
            GradientStop { position: 0.5; color:Qt.rgba(0.115,0.115,0.115,0.96); }
			GradientStop { position: 1.0; color:Qt.rgba(0.098,0.096,0.097,1.00); }
        }
    }

    Image{
        z : 0.1;
        anchors.centerIn: parent;
        width:parent.width*3;
        height: parent.height*3;
        source: "qrc:///background.png";
        fillMode: Image.Tile;
        horizontalAlignment: Image.AlignHCenter;
        verticalAlignment: Image.AlignVCenter;
        smooth: true;
        rotation: 31.2 + Math.random()*5.02 ;
 //       DropShadow{
 //           anchors.fill: parent;
 //           horizontalOffset: 0.5;
 //           verticalOffset: 0.5;
 //           radius: 1.0;
 //           samples: 17;
 //           color: "#80000000";
 //           source: parent;
 //       }
    }

    //粒子系统
    ParticleSystem {
        id: _id_particleSystem;
        anchors.fill:parent;
        z:3;
    }

    //发射器
    Emitter {
        id: _id_emitter_0 ;
        system: _id_particleSystem;

        anchors.fill: parent ;

        size: 9 ;
        endSize: 11.2 ;
        sizeVariation: 0.05 ;

        emitRate: 50000 ;

        lifeSpan: 555 ;
        lifeSpanVariation: 50;

        maximumEmitted : get_maximumemitted_0() ;

        shape :MaskShape {
            id : _id_mask_shape_0;
            source: get_maskshape_file_name() ;
        }

        group : "group0" ;
        z:3;
    }

    Emitter {
        id: _id_emitter_1 ;
        system: _id_particleSystem;

        anchors.fill: parent ;

        size: 6 ;
        endSize: 9 ;
        sizeVariation: 1 ;

        emitRate: 50000 ;

        lifeSpan: 555 ;
        lifeSpanVariation: 50;

        maximumEmitted : get_maximumemitted_1() ;

        shape :MaskShape {
            id : _id_mask_shape_1 ;
            source: get_maskshape_file_name() ;
        }

        group : "group1" ;
        z : 3 ;
    }

    //粒子 0
    ImageParticle {
        id : _id_imageparticle_0 ;
        system: _id_particleSystem;
        source: "qrc:///glowdot.png";
        color : Qt.rgba(0.75,0.75,0.75,0.75)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
        rotation : 180 ;
        rotationVariation : 90;
        groups:["group0"];
        entryEffect : ImageParticle.Fade;
        z : 3 ;
    }

    //粒子 1
    ImageParticle {
        id : _id_imageparticle_1 ;
        system: _id_particleSystem;
        source: "qrc:///star.png";
        color : Qt.rgba(0.75,0.75,0.75,0.7)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
        rotation : 180 ;
        rotationVariation : 90;
        groups: ["group1"];
        z : 3 ;
    }

    /*change mask*/
    function change_image(){
        _id_particleSystem.stop()                                ;
        var tmpVar = Math.random()/6.3                           ;
        _id_root.color = Qt.rgba(0.05+tmpVar ,tmpVar ,tmpVar ,1) ;
        _id_mask_shape_0.source      = get_maskshape_file_name() ;
        _id_mask_shape_1.source      = _id_mask_shape_0.source   ;
        _id_emitter_0.maximumEmitted = get_maximumemitted_0()    ;
        _id_emitter_1.maximumEmitted = get_maximumemitted_1()    ;
        _id_particleSystem.restart()                             ;
    }

    function get_maskshape_file_name(){
        return "file://" + myapp.qmlappdir() + "/tmp/shaped" + theCounter + ".png" ;
    }

    function get_maximumemitted_0(){
        return Math.min(16383, (1123.0 * 0.15 ) * myapp.getPointRate() );
    }

    function get_maximumemitted_1(){
        return Math.min(16383, (1123.0 *0.85 ) * myapp.getPointRate() );
    }

}


/**
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles/
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles-2/
**/




