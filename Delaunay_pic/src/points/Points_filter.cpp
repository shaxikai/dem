#include "Points_filter.h"

#include <algorithm>

Points_filter::Points_filter(vector<Point2d>& pointPixs_,
                             vector<Point3d>& pointClouds_)
                        : pointPixs(pointPixs_), pointClouds(pointClouds_)
{

}

void Points_filter::pixFilter() {
    vector<int> id;
    for (int i=0; i<pointPixs.size()-1; ++i) {
        for (int j=i+1; j<pointPixs.size(); ++j) {
            if ((int)pointPixs[i].x==(int)pointPixs[j].x && (int)pointPixs[i].y==(int)pointPixs[j].y) {
                id.push_back(i);
            }
        }
    }

    int i_ = 0;
    for(vector<Point3d>::iterator it=pointClouds.begin(); it!=pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointClouds[id[i_]-i_].x && (int)(*it).y==(int)pointClouds[id[i_]-i_].y) {
            it=pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=pointPixs.begin(); it!=pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointPixs[id[i_]-i_].x && (int)(*it).y==(int)pointPixs[id[i_]-i_].y) {
            it=pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptcFilter() {
    vector<int> id;
    for (int i=0; i<pointClouds.size(); ++i) {
        for (int j=0; j<pointClouds.size(); ++j) {
            if (i!=j && (int)pointClouds[i].x==(int)pointClouds[j].x && (int)pointClouds[i].y==(int)pointClouds[j].y) {
                if (pointClouds[i].z > pointClouds[j].z) id.push_back(j);
                else id.push_back(i);
            }
        }
    }
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());


    int i_ = 0;
    for(vector<Point3d>::iterator it=pointClouds.begin(); it!=pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointClouds[id[i_]-i_].x && (int)(*it).y==(int)pointClouds[id[i_]-i_].y) {
            it=pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=pointPixs.begin(); it!=pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointPixs[id[i_]-i_].x && (int)(*it).y==(int)pointPixs[id[i_]-i_].y) {
            it=pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptcRansac() {
    int thresholdZ = 20;

    int nPoints = pointClouds.size();
    if(nPoints < 10)
    {
        cout << "need more points" << endl;
    }

    int nRansacs = nPoints;
    pi::Point3d v3BestMean;
    pi::Point3d v3BestNormal;
    double dBestDistSquared = 9999999999999999.9;

    for(int i=0; i<nRansacs; i++)
    {
        //cout << i << endl;
        int nA = rand() % nPoints;
        int nB = nA;
        int nC = nA;
        while(nB == nA)
            nB = rand() % nPoints;
        while(nC == nA || nC==nB)
            nC = rand() % nPoints;

        pi::Point3d v3Mean = 0.33333333 * (pointClouds[nA] +
                                           pointClouds[nB] +
                                           pointClouds[nC]);

        pi::Point3d v3CA = pointClouds[nC]  - pointClouds[nA];
        pi::Point3d v3BA = pointClouds[nB]  - pointClouds[nA];
        pi::Point3d v3Normal = v3CA ^ v3BA;
        if(v3Normal * v3Normal  == 0)
            continue;
        v3Normal = v3Normal.normalize();

        double dSumError = 0.0;
        for(unsigned int i=0; i<nPoints; i++)
        {
            pi::Point3d v3Diff = pointClouds[i] - v3Mean;
            double dDistSq = v3Diff * v3Diff;

            if(dDistSq == 0.0)
                continue;

            double dNormDist = fabs(v3Diff * v3Normal);

            if(dNormDist > thresholdZ)
                dNormDist = thresholdZ;

            dSumError += dNormDist;
        }
        if(dSumError < dBestDistSquared)
        {
            dBestDistSquared = dSumError;
            v3BestMean = v3Mean;
            v3BestNormal = v3Normal;
        }
    }

    vector<int> id;

    for(int i=0; i<nPoints; i++)
    {
        pi::Point3d v3Diff = pointClouds[i] - v3BestMean;
        double dDistSq = v3Diff * v3Diff;

        if(dDistSq == 0.0)
            continue;

        double dNormDist = fabs(v3Diff * v3BestNormal);
        if(dNormDist > thresholdZ)
            id.push_back(i);
    }

    int i_ = 0;
    for(vector<Point3d>::iterator it=pointClouds.begin(); it!=pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointClouds[id[i_]-i_].x && (int)(*it).y==(int)pointClouds[id[i_]-i_].y) {
            it=pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=pointPixs.begin(); it!=pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)pointPixs[id[i_]-i_].x && (int)(*it).y==(int)pointPixs[id[i_]-i_].y) {
            it=pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptsFilter() {
    this->pixFilter();
    this->ptcRansac();
    this->ptcFilter();
}
