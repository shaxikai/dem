bool saveMapFusion(GSLAM::MapPtr slamMap,std::string file2save="mapfusion.txt")
{
    cout<<"Saving MapFusion File to "<<file2save<<endl;
    ofstream ofs(file2save.c_str());
    if(!ofs.is_open()) return false;

    GSLAM::FrameArray frames;
    slamMap->getFrames(frames);
    sort(frames.begin(),frames.end(),compareFr);

    for(GSLAM::FramePtr& fr:frames)
    {
        GSLAM::SE3   frPose=fr->getPose();
        GSLAM::SE3   w2c=frPose.inverse();
        string imagePath;
        fr->call("GetImagePath",&imagePath);
        if(imagePath.empty()) continue;
        GSLAM::Camera camIn=fr->getCamera();
        std::vector<double> camInParas=camIn.getParameters();
        std::map<GSLAM::PointID,size_t> observes;
        fr->getObservations(observes);
        std::vector<std::pair<GSLAM::Point2d,GSLAM::Point2d>> kpIdepthInfo;
        kpIdepthInfo.reserve(observes.size());
        for(std::pair<GSLAM::PointID,size_t> obs:observes)
        {
            GSLAM::PointPtr pt=slamMap->getPoint(obs.first);
            if(!pt) continue;
            GSLAM::Point2f featPt;
            if(!fr->getKeyPoint(obs.second,featPt)) continue;
            GSLAM::Point3d ptPlane=camIn.UnProject(featPt.x,featPt.y);
            GSLAM::Point3d pc=w2c*pt->getPose();
            if(pc.z<=0.01) continue;
            kpIdepthInfo.push_back(make_pair(GSLAM::Point2d(ptPlane.x,ptPlane.y),
                                             GSLAM::Point2d(1./pc.z,-1)));

        }
        auto t=frPose.get_translation();
        auto r=frPose.get_rotation();
        ofs.precision(12);
        ofs<<imagePath
          <<", "<<t.x<<", "<<t.y<<", "<<t.z<<", "<<r.x<<", "<<r.y<<", "<<r.z<<", "<<r.w
          <<", "<<camInParas.size();
        ofs.precision(6);
        for(double para:camInParas) ofs<<", "<<para;
        ofs<<", "<<kpIdepthInfo.size();
        for(std::pair<GSLAM::Point2d,GSLAM::Point2d>& kp:kpIdepthInfo)
        {
            ofs<<", "<<kp.first.x<<", "<<kp.first.y<<", "<<kp.second.x<<", "<<kp.second.y;
        }
        ofs<<endl;
    }


    return true;
}

