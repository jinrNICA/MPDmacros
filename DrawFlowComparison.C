#include <TROOT.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TFile.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <iostream>

void DrawFlowComparison()
{
  const std::string particle_name [] = {"Pions", "Kaons", "Protons"};
  const std::string particle_title [] = {"(#pi^{+})", "(K^{+})", "(p)"};
  const std::string centrality_title [] = {"10-20%", "20-40%"};
  const int profile_marker_style []  =  {21, 25};
  const int profile_color []         =  {1, 4};
  const std::string draw_option []   = {"e1","e1same"};
  const std::string v_harmonic []    = {"v1","v2"};
  const std::string Title_harmonic []= {"v_{1}","v_{2}"};
  const std::string statistics []    = {"GEANT3 PID", "(TOF+TPC) PID"};
  const std::string leg_name []      = {"true", "reco"};
  
  const std::pair<double, double> leg_X      = {0.2,0.955};
  const std::pair<double, double> leg_Y      = {0.8,0.955};
  
  TStyle* style = new TStyle("Default","Default style");
  style->SetTitleSize(0.06,"X");
  style->SetTitleSize(0.06,"Y");
  style->SetTitleOffset(1.1,"Y");
  style->SetTitleOffset(0.9,"X");
  style->SetFrameLineWidth(2);
  style->SetFrameFillColor(0);
  style->SetPadColor(0);
  style->SetLabelSize(0.04,"X");
  style->SetLabelSize(0.04,"Y");
  style->SetPadTopMargin(0.1);
  style->SetPadBottomMargin(0.12);
  style->SetPadLeftMargin(0.15);
  style->SetPadTopMargin(0.02);
  style->SetPadRightMargin(0.03);
  style->SetMarkerSize(1.2);
  style->SetErrorX(0);
  style->SetOptStat(0);
  style->SetCanvasColor(0);
  style->SetTitleFillColor(0);
  style->SetTitleBorderSize(0);
  style->SetCanvasBorderMode(0);
  style->SetLegendBorderSize(0);
  style->SetPadBorderMode(0);
  style->SetLineWidth(2);

  style->cd();
  
  std::map<int, std::vector<std::pair<double, double> > > v1ProfY;
  v1ProfY[0].push_back({-0.048,0.012});
  v1ProfY[0].push_back({-0.019,0.044});
  v1ProfY[0].push_back({ 0.,0.059});
  v1ProfY[1].push_back({-0.059,0.025});
  v1ProfY[1].push_back({-0.026,0.076});
  v1ProfY[1].push_back({-0.0053,0.048});
  std::map<int, std::vector<std::pair<double, double> > > v2ProfY;
  v2ProfY[0].push_back({ 0.022,0.096});
  v2ProfY[0].push_back({-0.007,0.102});
  v2ProfY[0].push_back({ 0.,0.092});
  v2ProfY[1].push_back({ 0.012,0.096});
  v2ProfY[1].push_back({ 0.002,0.105});
  v2ProfY[1].push_back({ 0.,0.115});
  
  std::map<int, std::vector<std::pair<double, double> > > v1YProfY;
  {
    v1YProfY[0].push_back({-0.12,0.22});
    v1YProfY[0].push_back({-0.05,0.05});
    v1YProfY[0].push_back({-0.12,0.18});
    v1YProfY[1].push_back({-0.12,0.22});
    v1YProfY[1].push_back({-0.05,0.05});
    v1YProfY[1].push_back({-0.05,0.08});
  }
  std::map<int, std::vector<std::pair<double, double> > > v2YProfY;
  {
    v2YProfY[0].push_back({ 0.02,0.039});
    v2YProfY[0].push_back({ 0.,0.072});
    v2YProfY[0].push_back({ 0.,0.099});
    v2YProfY[1].push_back({ 0.025,0.049});
    v2YProfY[1].push_back({ 0.,0.072});
    v2YProfY[1].push_back({ 0.,0.105});
  }
  
  std::vector<TFile*> vFile;
  vFile.push_back(new TFile("/home/peter/flow-11gev-pions4MPDG.root","read"));
  vFile.push_back(new TFile("/home/peter/flow-11gev-kaons4MPDG.root","read"));
  vFile.push_back(new TFile("/home/peter/flow-11gev-protons4MPDG.root","read"));

  vFile.push_back(new TFile("/home/peter/flow-11gev-pions4M.root","read"));
  vFile.push_back(new TFile("/home/peter/flow-11gev-kaons4M.root","read"));
  vFile.push_back(new TFile("/home/peter/flow-11gev-protons4M.root","read"));
  
  std::map<int,std::vector<TProfile*> > mFlow;
  std::map<int,std::vector<TCanvas*> >  mCanv;
  std::map<int,std::vector<TLegend*> >  mLeg;
  std::string name;
  for (int iFile=0; iFile < vFile.size(); iFile++){
    name  = particle_name[(int)iFile%3];
    mCanv[0].push_back(new TCanvas((name + "0" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", " + statistics[(int) iFile/3]).c_str(),500,500));
    mLeg[0].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlow[0].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_pt[0][0]") );
    mFlow[1].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_pt_divided[0][0][0][1]") );
    mCanv[1].push_back(new TCanvas((name + "1" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", " + statistics[(int) iFile/3]).c_str(),500,500));
    mLeg[1].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlow[2].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_pt[1][0]") );
    mFlow[3].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_pt_divided[1][0][0][1]") );
    mCanv[2].push_back(new TCanvas((name + "2" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", " + statistics[(int) iFile/3]).c_str(),500,500));
    mLeg[2].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlow[4].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_pt[0][1]") );
    mFlow[5].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_pt_divided[0][1][0][1]") );
    mCanv[3].push_back(new TCanvas((name + "3" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", " + statistics[(int) iFile/3]).c_str(),500,500));
    mLeg[3].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlow[6].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_pt[1][1]") );
    mFlow[7].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_pt_divided[1][1][0][1]") );
  }
  
  for (int iFile=0; iFile < vFile.size(); iFile++){
    for (std::map<int,std::vector<TProfile*> >::iterator iProf = mFlow.begin(); iProf != mFlow.end(); iProf++){
      std::cout << "mCanv[" << (int) iProf->first / 2 << "] Writes from file: " << vFile.at(iFile) -> GetName() <<std::endl;
      std::cout << "    " << mFlow[iProf->first].at(iFile) -> GetName() << "- with option: " << draw_option[(int) iProf->first%2] <<std::endl;
      mCanv[(int) iProf->first / 2].at(iFile) -> cd();
      mFlow[iProf->first].at(iFile) -> SetMarkerStyle(profile_marker_style[(int) iProf->first%2]);
      //mFlow[iProf->first].at(iFile) -> SetMarkerSize(1.2);
      mFlow[iProf->first].at(iFile) -> SetLineColor(profile_color[(int) iProf->first%2]);
      mFlow[iProf->first].at(iFile) -> SetMarkerColor(profile_color[(int) iProf->first%2]);
      if (iFile != 1 && iFile != 4) mFlow[iProf->first].at(iFile) -> GetXaxis() -> SetRangeUser(0.21,1.99);
      else                          mFlow[iProf->first].at(iFile) -> GetXaxis() -> SetRangeUser(0.21,1.59);
      mFlow[iProf->first].at(iFile) -> GetXaxis() -> SetTitleSize(0.06);
      mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetTitleSize(0.06);
      mFlow[iProf->first].at(iFile) -> GetXaxis() -> SetLabelSize(0.04);
      mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetLabelSize(0.04);
      mFlow[iProf->first].at(iFile) -> GetXaxis() -> SetTitleOffset(0.8);
      mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetTitleOffset(1.15);
      if ((int)iProf->first/4 == 0)
        mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetRangeUser(v1ProfY[(int) iProf->first/2%2].at((int)iFile%3).first,v1ProfY[(int) iProf->first/2%2].at((int)iFile%3).second);
      if ((int)iProf->first/4 == 1)
        mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetRangeUser(v2ProfY[(int) iProf->first/2%2].at((int)iFile%3).first,v2ProfY[(int) iProf->first/2%2].at((int)iFile%3).second);
      mFlow[iProf->first].at(iFile) -> GetYaxis() -> SetTitle(Title_harmonic[(int)iProf->first/4].c_str());
      //mFlow[iProf->first].at(iFile) -> SetTitle(mCanv[(int) iProf->first / 2].at(iFile) -> GetTitle());
      mFlow[iProf->first].at(iFile) -> SetTitle("");
      if ((int) iProf->first % 2 == 0){
        mLeg[(int) iProf->first / 2].at(iFile) -> SetHeader(("Au-Au #sqrt{s_{NN}} = 11 GeV, " + centrality_title[(int) iProf->first / 2 % 2] + ", GEANT3, UrQMD, 4M events").c_str(),"C");
        mLeg[(int) iProf->first / 2].at(iFile) -> AddEntry((TObject*) NULL, mCanv[(int) iProf->first / 2].at(iFile) -> GetTitle(),"");
      }
      mLeg[(int) iProf->first / 2].at(iFile) -> AddEntry(mFlow[iProf->first].at(iFile),leg_name[(int) iProf->first % 2].c_str());
      mLeg[(int) iProf->first / 2].at(iFile) -> Draw();
      mFlow[iProf->first].at(iFile) -> Draw(draw_option[(int) iProf->first%2].c_str());
          name = "/home/peter/Documents/WorkLocal/MPD/Pics/PIDFlow/MacroOutput/c_"  + 
                (std::string)mCanv[(int) iProf->first / 2].at(iFile) -> GetName() + ".pdf";  
      mCanv[(int) iProf->first / 2].at(iFile) -> Print(name.c_str(),"pdf");
    }
  }
  
  std::map<int,std::vector<TProfile*> > mFlowRap;
  std::map<int,std::vector<TCanvas*> >  mCanvRap;
  std::map<int,std::vector<TLegend*> >  mLegRap;
  TLine*   line = new TLine();
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  for (int iFile=0; iFile < vFile.size(); iFile++){
    name  = particle_name[(int)iFile%3];
    mCanvRap[0].push_back(new TCanvas((name + "(rapidity)0" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", Centrality 10-20%, " + statistics[(int) iFile/3]).c_str(),500,500));
    mLegRap[0].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlowRap[0].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_rapidity[0][0]") );
    mFlowRap[1].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_rapidity_divided[0][0][0][1]") );
    mCanvRap[1].push_back(new TCanvas((name + "(rapidity)1" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", Centrality 20-40%, " + statistics[(int) iFile/3]).c_str(),500,500));
    mLegRap[1].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlowRap[2].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_rapidity[1][0]") );
    mFlowRap[3].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_rapidity_divided[1][0][0][1]") );
    mCanvRap[2].push_back(new TCanvas((name + "(rapidity)2" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", Centrality 10-20%, " + statistics[(int) iFile/3]).c_str(),500,500));
    mLegRap[2].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlowRap[4].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_rapidity[0][1]") );
    mFlowRap[5].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_rapidity_divided[0][1][0][1]") );
    mCanvRap[3].push_back(new TCanvas((name + "(rapidity)3" + std::to_string(iFile)).c_str(),(name + " " + particle_title[(int)iFile%3] + ", Centrality 20-40%, " + statistics[(int) iFile/3]).c_str(),500,500));
    mLegRap[3].push_back(new TLegend(leg_X.first, leg_Y.first, leg_X.second, leg_Y.second));
    mFlowRap[6].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_RP_vs_rapidity[1][1]") );
    mFlowRap[7].push_back((TProfile*) vFile.at(iFile) -> Get("p_flow_wrt_full_vs_rapidity_divided[1][1][0][1]") );
  }
  
  for (int iFile=0; iFile < vFile.size(); iFile++){
    for (std::map<int,std::vector<TProfile*> >::iterator iProf = mFlowRap.begin(); iProf != mFlowRap.end(); iProf++){
      std::cout << "mCanvRap[" << (int) iProf->first / 2 << "] Writes from file: " << vFile.at(iFile) -> GetName() <<std::endl;
      std::cout << "    " << mFlowRap[iProf->first].at(iFile) -> GetName() << "- with option: " << draw_option[(int) iProf->first%2] <<std::endl;
      mCanvRap[(int) iProf->first / 2].at(iFile) -> cd();
      mFlowRap[iProf->first].at(iFile) -> SetMarkerStyle(profile_marker_style[(int) iProf->first%2]);
      //mFlowRap[iProf->first].at(iFile) -> SetMarkerSize(2.);
      mFlowRap[iProf->first].at(iFile) -> SetLineColor(profile_color[(int) iProf->first%2]);
      mFlowRap[iProf->first].at(iFile) -> SetMarkerColor(profile_color[(int) iProf->first%2]);
      mFlowRap[iProf->first].at(iFile) -> GetXaxis() -> SetRangeUser(-1.39,1.39);
      mFlowRap[iProf->first].at(iFile) -> GetXaxis() -> SetTitle("y");
      mFlowRap[iProf->first].at(iFile) -> GetXaxis() -> SetTitleSize(0.06);
      mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetTitleSize(0.06);
      mFlowRap[iProf->first].at(iFile) -> GetXaxis() -> SetLabelSize(0.04);
      mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetLabelSize(0.04);
      mFlowRap[iProf->first].at(iFile) -> GetXaxis() -> SetTitleOffset(0.8);
      mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetTitleOffset(1.15);
      if ((int)iProf->first/4 == 0)
        mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetRangeUser(v1YProfY[(int) iProf->first/2%2].at((int)iFile%3).first,v1YProfY[(int) iProf->first/2%2].at((int)iFile%3).second);
      if ((int)iProf->first/4 == 1)
        mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetRangeUser(v2YProfY[(int) iProf->first/2%2].at((int)iFile%3).first,v2YProfY[(int) iProf->first/2%2].at((int)iFile%3).second);
      mFlowRap[iProf->first].at(iFile) -> GetYaxis() -> SetTitle(Title_harmonic[(int)iProf->first/4].c_str());
      //mFlowRap[iProf->first].at(iFile) -> SetTitle(mCanvRap[(int) iProf->first / 2].at(iFile) -> GetTitle());
      mFlowRap[iProf->first].at(iFile) -> SetTitle("");
      if ((int) iProf->first % 2 == 0){
        mLegRap[(int) iProf->first / 2].at(iFile) -> SetHeader(("Au-Au #sqrt{s_{NN}} = 11 GeV, " + centrality_title[(int) iProf->first / 2 % 2] + ", GEANT3, UrQMD, 4M events").c_str(),"C");
        mLegRap[(int) iProf->first / 2].at(iFile) -> AddEntry((TObject*) NULL, mCanv[(int) iProf->first / 2].at(iFile) -> GetTitle(),"");
      }
      mLegRap[(int) iProf->first / 2].at(iFile) -> AddEntry(mFlowRap[iProf->first].at(iFile),leg_name[(int) iProf->first % 2].c_str());
      mLegRap[(int) iProf->first / 2].at(iFile) -> Draw();
      mFlowRap[iProf->first].at(iFile) -> Draw(draw_option[(int) iProf->first%2].c_str());
      line->DrawLine(-1.39,0.,1.39,0.);
          name = "/home/peter/Documents/WorkLocal/MPD/Pics/PIDFlow/MacroOutput/c_"  + 
                (std::string)mCanvRap[(int) iProf->first / 2].at(iFile) -> GetName() + ".pdf";  
      mCanvRap[(int) iProf->first / 2].at(iFile) -> Print(name.c_str(),"pdf");
    }
  }
  
  return;
}


int main(){
  DrawFlowComparison();
  return 0;
}
