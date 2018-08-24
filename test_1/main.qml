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
    color : Qt.rgba( Math.random()/6.3 ,Math.random()/6.2 ,Math.random()/6.1 ,1) ;

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

        size: 12 ;
        endSize: 18 ;
        sizeVariation: 2.5 ;

        emitRate: 50000 ;

        lifeSpan: 555 ;
        lifeSpanVariation: 50;

        maximumEmitted : get_maximumemitted_0() ;

        shape :MaskShape {
            id : _id_mask_shape_0;
            source: get_maskshape_file_name() ;
        }

        group : "group0" ;

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

    }

    //粒子 0
    ImageParticle {
        id : _id_imageparticle_0 ;
        system: _id_particleSystem;
        source: "qrc:///glowdot.png";
        color : Qt.rgba(0.75,0.75,0.75,0.6)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
		rotation : 180 ;
		rotationVariation : 90; 
        groups:["group0"]
    }

    //粒子 1
    ImageParticle {
        id : _id_imageparticle_1 ;
        system: _id_particleSystem;
        source: "qrc:///star.png";
        color : Qt.rgba(0.75,0.75,0.75,0.5)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
		rotation : 180 ;
		rotationVariation : 90; 
        groups: ["group1"]
    }

    /*change mask*/
    function change_image(){
        _id_particleSystem.stop()                                ;
        _id_root.color = Qt.rgba( Math.random()/6.3 ,Math.random()/6.2 ,Math.random()/6.1 ,1);
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
        return (1123.0 * 0.36 ) * myapp.getPointRate() ;
    }

    function get_maximumemitted_1(){
        return (1123.0 *0.65 ) * myapp.getPointRate() ;
    }

}


/**
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles/
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles-2/
**/




