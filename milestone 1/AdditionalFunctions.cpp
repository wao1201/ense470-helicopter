//http://www.openscenegraph.org/projects/osg/wiki/Support/Tutorials/CameraControlNodeFollowing

#include <osg/PositionAttitudeTransform>
#include <osgGA/CameraManipulator>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>

struct updateAccumlatedMatrix : public osg::NodeCallback
    {
       virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
       {
          matrix = osg::computeWorldToLocal(nv->getNodePath() );
          traverse(node,nv);
       }
       osg::Matrix matrix;
    }; 

    struct transformAccumulator
    {
    public: 
       transformAccumulator();
       bool attachToGroup(osg::Group* g);
       osg::Matrix getMatrix();
    protected:
       osg::ref_ptr<osg::Group> parent;
       osg::Node* node;
       updateAccumlatedMatrix* mpcb;
    };



    transformAccumulator::transformAccumulator()
    {
       parent = NULL;
       node = new osg::Node;
       mpcb = new updateAccumlatedMatrix();
       node->setUpdateCallback(mpcb);
    }

    osg::Matrix transformAccumulator::getMatrix()
    {
       return mpcb->matrix;
    }

    bool transformAccumulator::attachToGroup(osg::Group* g)
    // Don't call this method from within a callback (see this post.) 
    {
       bool success = false;
       if (parent != NULL)
       {
          int n = parent->getNumChildren();
          for (int i = 0; i < n; i++)
          {
             if (node == parent->getChild(i) )
             {
                parent->removeChild(i,1);
                success = true;
             }
          }
          if (! success)
          {
             return success;
          }
       }
       g->addChild(node);
       return true;
    }

    class followNodeCameraManipulator : public osgGA::CameraManipulator
    {
    public:
       followNodeCameraManipulator( transformAccumulator* ta); 
       bool handle (const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa);
       void updateTheMatrix();
       virtual void setByMatrix(const osg::Matrixd& mat);
       virtual void setByInverseMatrix(const osg::Matrixd&mat);
       virtual osg::Matrixd getInverseMatrix() const;
       virtual osg::Matrixd getMatrix() const;
    protected:
       ~followNodeCameraManipulator() {}
       transformAccumulator* worldCoordinatesOfNode;
       osg::Matrixd theMatrix;
    };


    followNodeCameraManipulator::followNodeCameraManipulator( transformAccumulator* ta)
    {
       worldCoordinatesOfNode = ta; theMatrix = osg::Matrixd::identity();
    }
    void followNodeCameraManipulator::updateTheMatrix()
    {
       theMatrix = worldCoordinatesOfNode->getMatrix();
    }
    osg::Matrixd followNodeCameraManipulator::getMatrix() const
    {
       return theMatrix;
    }
    osg::Matrixd followNodeCameraManipulator::getInverseMatrix() const
    {
    // rotate the matrix from Y up to Z up. 
       osg::Matrixd m;
       m = theMatrix * osg::Matrixd::rotate(-3.14/2.0, osg::Vec3(1,0,0) );
       return m;
    }
    void followNodeCameraManipulator::setByMatrix(const osg::Matrixd& mat)
    {
       theMatrix = mat;
    }
    void followNodeCameraManipulator::setByInverseMatrix(const osg::Matrixd& mat)
    {
       theMatrix = mat.inverse(mat);
    } 

    bool followNodeCameraManipulator::handle
    (const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa)
    {
       switch(ea.getEventType())
       {
          case (osgGA::GUIEventAdapter::FRAME):
          {
             updateTheMatrix();
             return false;
          }
       }
       return false;
    }