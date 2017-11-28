#include "Points_filter.h"

#include <algorithm>

Points_filter::Points_filter(Frame& frame_) : frame(frame_)
{

}

void Points_filter::setFrame(Frame& frame_) {
    frame = frame_;
}

void Points_filter::pixFilter() {
    vector<int> id;
    for (int i=0; i<frame.pointPixs.size()-1; ++i) {
        for (int j=i+1; j<frame.pointPixs.size(); ++j) {
            if ((int)frame.pointPixs[i].x==(int)frame.pointPixs[j].x && (int)frame.pointPixs[i].y==(int)frame.pointPixs[j].y) {
                id.push_back(i);
            }
        }
    }

    int i_ = 0;
    for(vector<Point3d>::iterator it=frame.pointClouds.begin(); it!=frame.pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointClouds[id[i_]-i_].x && (int)(*it).y==(int)frame.pointClouds[id[i_]-i_].y) {
            it=frame.pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=frame.pointPixs.begin(); it!=frame.pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointPixs[id[i_]-i_].x && (int)(*it).y==(int)frame.pointPixs[id[i_]-i_].y) {
            it=frame.pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptcFilter() {
    vector<int> id;
    for (int i=0; i<frame.pointClouds.size(); ++i) {
        for (int j=0; j<frame.pointClouds.size(); ++j) {
            if (i!=j && (int)frame.pointClouds[i].x==(int)frame.pointClouds[j].x && (int)frame.pointClouds[i].y==(int)frame.pointClouds[j].y) {
                if (frame.pointClouds[i].z > frame.pointClouds[j].z) id.push_back(j);
                else id.push_back(i);
            }
        }
    }
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());


    int i_ = 0;
    for(vector<Point3d>::iterator it=frame.pointClouds.begin(); it!=frame.pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointClouds[id[i_]-i_].x && (int)(*it).y==(int)frame.pointClouds[id[i_]-i_].y) {
            it=frame.pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=frame.pointPixs.begin(); it!=frame.pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointPixs[id[i_]-i_].x && (int)(*it).y==(int)frame.pointPixs[id[i_]-i_].y) {
            it=frame.pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptcRansac() {
    int thresholdZ = 20;

    int nPoints = frame.pointClouds.size();
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

        pi::Point3d v3Mean = 0.33333333 * (frame.pointClouds[nA] +
                                           frame.pointClouds[nB] +
                                           frame.pointClouds[nC]);

        pi::Point3d v3CA = frame.pointClouds[nC]  - frame.pointClouds[nA];
        pi::Point3d v3BA = frame.pointClouds[nB]  - frame.pointClouds[nA];
        pi::Point3d v3Normal = v3CA ^ v3BA;
        if(v3Normal * v3Normal  == 0)
            continue;
        v3Normal = v3Normal.normalize();

        double dSumError = 0.0;
        for(unsigned int i=0; i<nPoints; i++)
        {
            pi::Point3d v3Diff = frame.pointClouds[i] - v3Mean;
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
        pi::Point3d v3Diff = frame.pointClouds[i] - v3BestMean;
        double dDistSq = v3Diff * v3Diff;

        if(dDistSq == 0.0)
            continue;

        double dNormDist = fabs(v3Diff * v3BestNormal);
        if(dNormDist > thresholdZ)
            id.push_back(i);
    }

    int i_ = 0;
    for(vector<Point3d>::iterator it=frame.pointClouds.begin(); it!=frame.pointClouds.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointClouds[id[i_]-i_].x && (int)(*it).y==(int)frame.pointClouds[id[i_]-i_].y) {
            it=frame.pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=frame.pointPixs.begin(); it!=frame.pointPixs.end();) {
        if (i_ == id.size()) break;
        if ((int)(*it).x==(int)frame.pointPixs[id[i_]-i_].x && (int)(*it).y==(int)frame.pointPixs[id[i_]-i_].y) {
            it=frame.pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
}

void Points_filter::ptsPrefilter() {
    this->pixFilter();
    this->ptcRansac();
    this->ptcFilter();
}

int Points_filter::ptsOutfilter() {
    vector<Point3d>& pointClouds = frame.pointClouds;
    vector<Point2d>& pointPixs   = frame.pointPixs;
    vector<TriEle> & tris = frame.tris;

    vector<int> out_id;

    for (int i=0; i<pointClouds.size(); ++i) {
        std::vector<int> tris_id = frame.pt_getTris(i);

        int count = 0;
        vector<int> neiPts;

        for (int j=0; j<tris_id.size(); ++j) {

            int line_pt1_id, line_pt2_id;

            if (tris[tris_id[j]].c_1 == i) {
                line_pt1_id = tris[tris_id[j]].c_2;
                line_pt2_id = tris[tris_id[j]].c_3;
            } else if (tris[tris_id[j]].c_2 == i) {
                line_pt1_id = tris[tris_id[j]].c_1;
                line_pt2_id = tris[tris_id[j]].c_3;
            } else if (tris[tris_id[j]].c_3 == i) {
                line_pt1_id = tris[tris_id[j]].c_1;
                line_pt2_id = tris[tris_id[j]].c_2;
            }

            neiPts.push_back(line_pt1_id);
            neiPts.push_back(line_pt2_id);

            double k_ = (pointClouds[line_pt2_id].y - pointClouds[line_pt1_id].y)/
                    (pointClouds[line_pt2_id].x - pointClouds[line_pt1_id].x);
            double b_ = pointClouds[line_pt1_id].y +
                    k_ * (pointClouds[i].x-pointClouds[line_pt1_id].x);

            if ( (pointClouds[i].x-pointClouds[line_pt1_id].x) *
                 (pointClouds[i].x-pointClouds[line_pt2_id].x) < 0 &&
                  pointClouds[i].y > b_ )
                count++;
        }

        sort(neiPts.begin(), neiPts.end());
        int out;
        for (out=1; out<neiPts.size(); out+=2) {
            if (neiPts[out] != neiPts[out-1]) break;
        }

        if (out-1 == neiPts.size() && count%2 == 0) {
            out_id.push_back(i);
        }
    }

    sort(out_id.begin(), out_id.end());
    out_id.erase(unique(out_id.begin(), out_id.end()), out_id.end());

    int i_ = 0;
    for(vector<Point3d>::iterator it=pointClouds.begin(); it!=pointClouds.end();)
    {
        if (i_ == out_id.size()) break;
        if ((int)(*it).x==(int)pointClouds[out_id[i_]-i_].x &&
            (int)(*it).y==(int)pointClouds[out_id[i_]-i_].y)
        {
            it=pointClouds.erase(it);
            ++i_;
        } else { ++it; }
    }

    i_ = 0;
    for(vector<Point2d>::iterator it=frame.pointPixs.begin(); it!=pointPixs.end();)
    {
        if (i_ == out_id.size()) break;
        if ((int)(*it).x==(int)pointPixs[out_id[i_]-i_].x &&
            (int)(*it).y==(int)pointPixs[out_id[i_]-i_].y)
        {
            it=pointPixs.erase(it);
            ++i_;
        } else { ++it; }
    }
    return out_id.size();
}
