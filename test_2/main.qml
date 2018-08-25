import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Particles 2.11
import QtGraphicalEffects 1.0

Rectangle {

    id : _id_root;
    width:  100;
    height: 100;
    border.width: 0;
    
    Image{
        id : _id_background_image;
        anchors.fill: parent ;
        smooth: true;
        fillMode: Image.Tile;
        horizontalAlignment: Image.AlignHCenter;
        verticalAlignment: Image.AlignVCenter;

 //      LinearGradient{
 //          id : _id_linegradient_;
 //          anchors.fill: parent;
 //          start: Qt.point(0, 0);
 //          end: Qt.point(0, 300);
 //          cached :false ;
 //          gradient: Gradient {
 //              GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0.5)  }
 //              GradientStop { position: 1.0; color: Qt.rgba(0.6,0.6,0.6,0.5) }
 //          }
 //      }
    }

    function image_changed(){
        _id_root.width = myapp.getImageWidth();
        _id_root.height = myapp.getImageHeight();
        //_id_linegradient_.start = Qt.point(0,0);
        //_id_linegradient_.end = Qt.point(_id_root.height, _id_root.height );
        _id_background_image.source = "file://" + myapp.getImagePath();
    }

    Component.onCompleted : image_changed() ;

    function get_maximumemitted_1(){ 
		return Math.min(16383, 8000.1*(_id_root.width*_id_root.height)/(640*480.0) );
	}

    function get_maximumemitted_0(){ 
		return Math.min(16383, 7000.2*(_id_root.width*_id_root.height)/(640*480.0) );
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

        group : "group1" ;
        z : 3 ;
    }

    //粒子 0
    ImageParticle {
        id : _id_imageparticle_0 ;
        system: _id_particleSystem;
        source: "qrc:///glowdot.png";
        color : Qt.rgba(0.275,0.275,0.275,0.75)
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
        color : Qt.rgba(0.275,0.275,0.275,0.7)
        blueVariation : 0.3;
        greenVariation : 0.3;
        redVariation : 0.3;
        alphaVariation: 0.3;
        rotation : 180 ;
        rotationVariation : 90;
        groups: ["group1"];
        z : 3 ;
    }

}


/**
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles/
https://www.devbean.net/2016/01/qt-study-road-2-qml-particles-2/
**/




