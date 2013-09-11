ofxCvFacialRecognitionVideo
===========================

Train a predictive model with images of a person and then recognize their face with a camera. Eh, kind of works :)

This is testing on Mountain Lion, latest bropenFrameworks.

Download this shiz and put it inside the ofxCv folder in addons:

openframeworks->addons->ofxCv

Here is what I did to create a training image:

1) took a sexy photo with photobooth

2) opened it in preview and cropped it down

3) placed it in the data/faces folder inside the example
openframeworks->addons->ofxCv->this_example->bin->data->faces

4) this will create a training image when the application is run.

compile and run the app (fingers crossed) and when you look into your camera your face should be highlighted in the list of peeps.

Big ups to Lab at Rockwell http://www.rockwellgroup.com/lab for the help.
