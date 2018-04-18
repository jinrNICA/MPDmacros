#include "TROOT.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1F.h"
#include <iostream>

#define _MAX_TRACKS 200000
void PrintPid(){
  TCanvas* c_ep = new TCanvas("c_ep","PID_dEdx_LogP" ,1000,1000);
  TCanvas* c_mp = new TCanvas("c_mp","PID_M2_LogP"   ,1000,1000);
  TCanvas* c_me = new TCanvas("c_me","PID_M2_dEdx"   ,1000,1000);
  TCanvas* c_m  = new TCanvas("c_m","PID_M2"        ,1000,1000);
  
  TCanvas* c1_ep = new TCanvas("c1_ep","PID_TPC_dEdx_LogP" ,1000,1000);
  TCanvas* c1_mp = new TCanvas("c1_mp","PID_TPC_M2_LogP"   ,1000,1000);
  TCanvas* c1_me = new TCanvas("c1_me","PID_TPC_M2_dEdx"   ,1000,1000);
  TCanvas* c1_m  = new TCanvas("c1_m","PID_TPC_M2"        ,1000,1000);
  
  TCanvas* c2_ep = new TCanvas("c2_ep","PID_TPC+TOF_dEdx_LogP" ,1000,1000);
  TCanvas* c2_mp = new TCanvas("c2_mp","PID_TPC+TOF_M2_LogP"   ,1000,1000);
  TCanvas* c2_me = new TCanvas("c2_me","PID_TPC+TOF_M2_dEdx"   ,1000,1000);
  TCanvas* c2_m  = new TCanvas("c2_m","PID_TPC+TOF_M2"        ,1000,1000);
  
  TFile * inFile = new TFile("~/Documents/WorkLocal/MPD/RootFiles/merged_0_clone.root","read");
  TTree * inTree = (TTree*) inFile->Get("cbmsim_reduced");
  
  TH2F  * h_ep_all      = new TH2F("h_ep_all"     ,"All;Log10(p [GeV/c]);dEdx, [a.u.]"          ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h_ep_pions    = new TH2F("h_ep_pions"   ,"Pions (TOF);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h_ep_kaons    = new TH2F("h_ep_kaons"   ,"Kaons (TOF);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h_ep_protons  = new TH2F("h_ep_protons" ,"Protons (TOF);Log10(p [GeV/c]);dEdx, [a.u.]",100,-1.04,1.54,1000,0.,50000.);
  
  TH2F  * h_mp_all      = new TH2F("h_mp_all"     ,"All;Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"          ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h_mp_pions    = new TH2F("h_mp_pions"   ,"Pions (TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h_mp_kaons    = new TH2F("h_mp_kaons"   ,"Kaons (TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h_mp_protons  = new TH2F("h_mp_protons" ,"Protons (TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}",100,-1.04,1.54,100,0.,2.);
  
  TH2F  * h_me_all      = new TH2F("h_me_all"     ,"All;m^{2}, [GeV/c]^{2};dEdx, [a.u.]"          ,100,0.,2.,1000,0.,50000.);
  TH2F  * h_me_pions    = new TH2F("h_me_pions"   ,"Pions (TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h_me_kaons    = new TH2F("h_me_kaons"   ,"Kaons (TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h_me_protons  = new TH2F("h_me_protons" ,"Protons (TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]",100,0.,2.,1000,0.,50000.); 
  
  TH1F  * h_m_all      = new TH1F("h_m_all"     ,"All;m^{2}, [GeV/c]^{2};N_{entries}"          ,100,0.,2.);
  TH1F  * h_m_pions    = new TH1F("h_m_pions"   ,"Pions (TOF);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h_m_kaons    = new TH1F("h_m_kaons"   ,"Kaons (TOF);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h_m_protons  = new TH1F("h_m_protons" ,"Protons (TOF);m^{2}, [GeV/c]^{2};N_{entries}",100,0.,2.);
  
  
  
  TH2F  * h1_ep_all      = new TH2F("h1_ep_all"     ,"All;Log10(p [GeV/c]);dEdx, [a.u.]"          ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h1_ep_pions    = new TH2F("h1_ep_pions"   ,"Pions (TPC);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h1_ep_kaons    = new TH2F("h1_ep_kaons"   ,"Kaons (TPC);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h1_ep_protons  = new TH2F("h1_ep_protons" ,"Protons (TPC);Log10(p [GeV/c]);dEdx, [a.u.]",100,-1.04,1.54,1000,0.,50000.);
  
  TH2F  * h1_mp_all      = new TH2F("h1_mp_all"     ,"All;Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"          ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h1_mp_pions    = new TH2F("h1_mp_pions"   ,"Pions (TPC);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h1_mp_kaons    = new TH2F("h1_mp_kaons"   ,"Kaons (TPC);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h1_mp_protons  = new TH2F("h1_mp_protons" ,"Protons (TPC);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}",100,-1.04,1.54,100,0.,2.);
  
  TH2F  * h1_me_all      = new TH2F("h1_me_all"     ,"All;m^{2}, [GeV/c]^{2};dEdx, [a.u.]"          ,100,0.,2.,1000,0.,50000.);
  TH2F  * h1_me_pions    = new TH2F("h1_me_pions"   ,"Pions (TPC);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h1_me_kaons    = new TH2F("h1_me_kaons"   ,"Kaons (TPC);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h1_me_protons  = new TH2F("h1_me_protons" ,"Protons (TPC);m^{2}, [GeV/c]^{2};dEdx, [a.u.]",100,0.,2.,1000,0.,50000.); 
  
  TH1F  * h1_m_all      = new TH1F("h1_m_all"     ,"All;m^{2}, [GeV/c]^{2};N_{entries}"          ,100,0.,2.);
  TH1F  * h1_m_pions    = new TH1F("h1_m_pions"   ,"Pions (TPC);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h1_m_kaons    = new TH1F("h1_m_kaons"   ,"Kaons (TPC);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h1_m_protons  = new TH1F("h1_m_protons" ,"Protons (TPC);m^{2}, [GeV/c]^{2};N_{entries}",100,0.,2.);
  
  
  
  TH2F  * h2_ep_all      = new TH2F("h2_ep_all"     ,"All;Log10(p [GeV/c]);dEdx, [a.u.]"          ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h2_ep_pions    = new TH2F("h2_ep_pions"   ,"Pions (TPC+TOF);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h2_ep_kaons    = new TH2F("h2_ep_kaons"   ,"Kaons (TPC+TOF);Log10(p [GeV/c]);dEdx, [a.u.]"  ,100,-1.04,1.54,1000,0.,50000.);
  TH2F  * h2_ep_protons  = new TH2F("h2_ep_protons" ,"Protons (TPC+TOF);Log10(p [GeV/c]);dEdx, [a.u.]",100,-1.04,1.54,1000,0.,50000.);

  TH2F  * h2_mp_all      = new TH2F("h2_mp_all"     ,"All;Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"          ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h2_mp_pions    = new TH2F("h2_mp_pions"   ,"Pions (TPC+TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h2_mp_kaons    = new TH2F("h2_mp_kaons"   ,"Kaons (TPC+TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}"  ,100,-1.04,1.54,100,0.,2.);
  TH2F  * h2_mp_protons  = new TH2F("h2_mp_protons" ,"Protons (TPC+TOF);Log10(p [GeV/c]);m^{2}, [GeV/c]^{2}",100,-1.04,1.54,100,0.,2.);

  TH2F  * h2_me_all      = new TH2F("h2_me_all"     ,"All;m^{2}, [GeV/c]^{2};dEdx, [a.u.]"          ,100,0.,2.,1000,0.,50000.);
  TH2F  * h2_me_pions    = new TH2F("h2_me_pions"   ,"Pions (TPC+TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h2_me_kaons    = new TH2F("h2_me_kaons"   ,"Kaons (TPC+TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]"  ,100,0.,2.,1000,0.,50000.);
  TH2F  * h2_me_protons  = new TH2F("h2_me_protons" ,"Protons (TPC+TOF);m^{2}, [GeV/c]^{2};dEdx, [a.u.]",100,0.,2.,1000,0.,50000.); 

  TH1F  * h2_m_all       = new TH1F("h2_m_all"     ,"All;m^{2}, [GeV/c]^{2};N_{entries}"          ,100,0.,2.);
  TH1F  * h2_m_pions     = new TH1F("h2_m_pions"   ,"Pions (TPC+TOF);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h2_m_kaons     = new TH1F("h2_m_kaons"   ,"Kaons (TPC+TOF);m^{2}, [GeV/c]^{2};N_{entries}"  ,100,0.,2.);
  TH1F  * h2_m_protons   = new TH1F("h2_m_protons" ,"Protons (TPC+TOF);m^{2}, [GeV/c]^{2};N_{entries}",100,0.,2.);
  
  //-------------------------------------------------------------------TOF-------------------------------------------------------------------// 
  
  c_ep->Divide(2,2);
  
  c_ep->cd(1);
  c_ep->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h_ep_all","","colz");
  std::cout << "h_ep_all" << std::endl;
  c_ep->cd(2);
  c_ep->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h_ep_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_ep_pions" << std::endl;
  c_ep->cd(3);
  c_ep->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h_ep_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_ep_kaons" << std::endl;
  c_ep->cd(4);
  c_ep->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h_ep_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9","colz");
  std::cout << "h_ep_protons" << std::endl;
  
  c_mp->Divide(2,2);
  
  c_mp->cd(1);
  c_mp->cd(1)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h_mp_all","","colz");
  std::cout << "h_mp_all" << std::endl;
  c_mp->cd(2);
  c_mp->cd(2)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h_mp_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_mp_pions" << std::endl;
  c_mp->cd(3);
  c_mp->cd(3)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h_mp_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_mp_kaons" << std::endl;
  c_mp->cd(4);
  c_mp->cd(4)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h_mp_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9","colz");
  std::cout << "h_mp_protons" << std::endl;
  
  c_me->Divide(2,2);
  
  c_me->cd(1);
  c_me->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h_me_all","","colz");
  std::cout << "h_me_all" << std::endl;
  c_me->cd(2);
  c_me->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h_me_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_me_pions" << std::endl;
  c_me->cd(3);
  c_me->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h_me_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1","colz");
  std::cout << "h_me_kaons" << std::endl;
  c_me->cd(4);
  c_me->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h_me_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9","colz");
  std::cout << "h_me_protons" << std::endl;
  
  c_m->Divide(2,2);
  
  c_m->cd(1);
  c_m->cd(1)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h_m_all","","colz");
  h_m_all->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h_m_all" << std::endl;
  c_m->cd(2);
  c_m->cd(2)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h_m_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1","colz");
  h_m_pions->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h_m_pions" << std::endl;
  c_m->cd(3);
  c_m->cd(3)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h_m_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1","colz");
  h_m_kaons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h_m_kaons" << std::endl;
  c_m->cd(4);
  c_m->cd(4)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h_m_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9","colz");
  h_m_protons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h_m_protons" << std::endl;
  c_m->Update();
  
  c_ep  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_ep.pdf");
  c_mp  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_mp.pdf");
  c_me  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_me.pdf");
  c_m   ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_m.pdf");
  
  c_ep  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_ep.png");
  c_mp  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_mp.png");
  c_me  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_me.png");
  c_m   ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tof_m.png");
  
  //-------------------------------------------------------------------TPC-------------------------------------------------------------------//
  
  c1_ep->Divide(2,2);
  
  c1_ep->cd(1);
  c1_ep->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h1_ep_all","","colz");
  std::cout << "h1_ep_all" << std::endl;
  c1_ep->cd(2);
  c1_ep->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h1_ep_pions","pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_ep_pions" << std::endl;
  c1_ep->cd(3);
  c1_ep->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h1_ep_kaons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_ep_kaons" << std::endl;
  c1_ep->cd(4);
  c1_ep->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h1_ep_protons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h1_ep_protons" << std::endl;
  
  c1_mp->Divide(2,2);
  
  c1_mp->cd(1);
  c1_mp->cd(1)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h1_mp_all","","colz");
  std::cout << "h1_mp_all" << std::endl;
  c1_mp->cd(2);
  c1_mp->cd(2)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h1_mp_pions","pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_mp_pions" << std::endl;
  c1_mp->cd(3);
  c1_mp->cd(3)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h1_mp_kaons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_mp_kaons" << std::endl;
  c1_mp->cd(4);
  c1_mp->cd(4)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h1_mp_protons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h1_mp_protons" << std::endl;
  
  c1_me->Divide(2,2);
  
  c1_me->cd(1);
  c1_me->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h1_me_all","","colz");
  std::cout << "h1_me_all" << std::endl;
  c1_me->cd(2);
  c1_me->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h1_me_pions","pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_me_pions" << std::endl;
  c1_me->cd(3);
  c1_me->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h1_me_kaons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h1_me_kaons" << std::endl;
  c1_me->cd(4);
  c1_me->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h1_me_protons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h1_me_protons" << std::endl;
  
  c1_m->Divide(2,2);
  
  c1_m->cd(1);
  c1_m->cd(1)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h1_m_all","","colz");
  h_m_all->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h1_m_all" << std::endl;
  c1_m->cd(2);
  c1_m->cd(2)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h1_m_pions","pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  h_m_pions->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h1_m_pions" << std::endl;
  c1_m->cd(3);
  c1_m->cd(3)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h1_m_kaons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  h_m_kaons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h1_m_kaons" << std::endl;
  c1_m->cd(4);
  c1_m->cd(4)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h1_m_protons","pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  h_m_protons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h1_m_protons" << std::endl;
  c1_m->Update();
 
  c1_ep ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_ep.pdf");
  c1_mp ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_mp.pdf");
  c1_me ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_me.pdf");
  c1_m  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_m.pdf");
  
  c1_ep ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_ep.png");
  c1_mp ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_mp.png");
  c1_me ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_me.png");
  c1_m  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_m.png");
  
  //-----------------------------------------------------------------TOF+TPC-----------------------------------------------------------------//
  
  c2_ep->Divide(2,2);
  
  c2_ep->cd(1);
  c2_ep->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h2_ep_all","","colz");
  std::cout << "h2_ep_all" << std::endl;
  c2_ep->cd(2);
  c2_ep->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h2_ep_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_ep_pions" << std::endl;
  c2_ep->cd(3);
  c2_ep->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h2_ep_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_ep_kaons" << std::endl;
  c2_ep->cd(4);
  c2_ep->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:TMath::Log10(p_mpd)>>h2_ep_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h2_ep_protons" << std::endl;
  
  c2_mp->Divide(2,2);
  
  c2_mp->cd(1);
  c2_mp->cd(1)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h2_mp_all","","colz");
  std::cout << "h2_mp_all" << std::endl;
  c2_mp->cd(2);
  c2_mp->cd(2)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h2_mp_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_mp_pions" << std::endl;
  c2_mp->cd(3);
  c2_mp->cd(3)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h2_mp_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_mp_kaons" << std::endl;
  c2_mp->cd(4);
  c2_mp->cd(4)->SetLogz();
  inTree->Draw("tof_mass2_mpd:TMath::Log10(p_mpd)>>h2_mp_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h2_mp_protons" << std::endl;
  
  c2_me->Divide(2,2);
  
  c2_me->cd(1);
  c2_me->cd(1)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h2_me_all","","colz");
  std::cout << "h2_me_all" << std::endl;
  c2_me->cd(2);
  c2_me->cd(2)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h2_me_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_me_pions" << std::endl;
  c2_me->cd(3);
  c2_me->cd(3)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h2_me_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  std::cout << "h2_me_kaons" << std::endl;
  c2_me->cd(4);
  c2_me->cd(4)->SetLogz();
  inTree->Draw("dEdx_tpc_mpd:tof_mass2_mpd>>h2_me_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  std::cout << "h2_me_protons" << std::endl;
  
  c2_m->Divide(2,2);
  
  c2_m->cd(1);
  c2_m->cd(1)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h2_m_all","","colz");
  h_m_all->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h2_m_all" << std::endl;
  c2_m->cd(2);
  c2_m->cd(2)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h2_m_pions","pid_tof_prob_pion_mpd > 0.9 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd > 0.9 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd < 0.1","colz");
  h_m_pions->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h2_m_pions" << std::endl;
  c2_m->cd(3);
  c2_m->cd(3)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h2_m_kaons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd > 0.9 && pid_tof_prob_proton_mpd < 0.1 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd > 0.9 && pid_tpc_prob_proton_mpd < 0.1","colz");
  h_m_kaons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h2_m_kaons" << std::endl;
  c2_m->cd(4);
  c2_m->cd(4)->SetLogy();
  inTree->Draw("tof_mass2_mpd>>h2_m_protons","pid_tof_prob_pion_mpd < 0.1 && pid_tof_prob_kaon_mpd < 0.1 && pid_tof_prob_proton_mpd > 0.9 && pid_tpc_prob_pion_mpd < 0.1 && pid_tpc_prob_kaon_mpd < 0.1 && pid_tpc_prob_proton_mpd > 0.9","colz");
  h_m_protons->GetYaxis()->SetRangeUser(90,2e6);
  std::cout << "h2_m_protons" << std::endl;
  c2_m->Update();
 
  c2_ep ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_ep.pdf");
  c2_mp ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_mp.pdf");
  c2_me ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_me.pdf");
  c2_m  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_m.pdf");
  
  c2_ep ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_ep.png");
  c2_mp ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_mp.png");
  c2_me ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_me.png");
  c2_m  ->SaveAs("/home/peter/Documents/WorkLocal/MPD/Framework/c_tpc_tof_m.png");
  
}
