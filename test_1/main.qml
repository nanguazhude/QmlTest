import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Particles 2.11
import QtGraphicalEffects 1.0

Rectangle {
    width:  640;
    height: 480;
    border.width: 0;
	z:0;
	color:Qt.rgba(0.171 ,0.17 ,0.17 ,1);
	   

    //粒子系统
    ParticleSystem {
        id: _id_particleSystem;
        anchors.fill:parent;
		z:3;
    }

    //发射器
    Emitter {
        id: _id_emitter;
        system: _id_particleSystem;
		
        anchors.fill: parent ;

        size: 5 ;
        endSize: 8 ;
        sizeVariation: 1.5 ;

        emitRate: 50000 ;

        lifeSpan: 555 ;
        lifeSpanVariation: 50;

        maximumEmitted : ( function(){ return 1123 * myapp.getPointRate() })() ;

        shape :MaskShape {
            id : _id_mask_shape;
            source: get_maskshape_file_name() ;
        }

    }

    //粒子 1
    ImageParticle {
        system: _id_particleSystem;
        source: "qrc:///glowdot.png";

        color : Qt.rgba(0.75,0.75,0.75,0.6)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
        autoRotation : true;
    }

    //粒子 2
   ImageParticle {
       system: _id_particleSystem;
       source: "qrc:///star.png";
 
       color : Qt.rgba(0.75,0.75,0.75,0.5)
       blueVariation : 0.3;
       greenVariation : 0.3;
       redVariation : 0.3;
       alphaVariation: 0.3;
       autoRotation : true;
   }

    /*change mask*/
    function change_image(){
        _id_particleSystem.stop();
        _id_mask_shape.source = "qrc:///_shaped.png"/*强制更换图片*/;
        _id_mask_shape.source = get_maskshape_file_name();
        _id_emitter.maximumEmitted = 1123 * myapp.getPointRate() ;
        _id_particleSystem.restart();
    }

    function get_maskshape_file_name(){
        return "file://" + myapp.qmlappdir() + "/shaped.png";
    }

}







