const Int_t n_energy     = 1;
const Int_t n_sorts      = 3;
const Int_t n_centrality = 2;
const Int_t n_harm       = 2;

const Int_t marker_flow_stl[2][3] ={{20,21,22},{24,25,26}};
const Int_t marker_res_color[]={1,2,4};
const Float_t res_range[2][2]        ={{0.21,1.2},{0.01,0.96}};
const Int_t   centrality_range[]     ={0,79};
const std::string particle_name [] = {"All", "Pions", "Protons", "Kaons"};
const std::pair<double, double>   eta_spectreY [] ={{0.9e5,0.9e7},{5e4,0.9e6},{2e4,0.5e6},{5e3,0.5e6}};
const std::pair<double, double>   pt_spectreY [] ={{2e1,5e8},{1e1,0.9e8},{1e2,0.9e8},{1e1,0.9e7}};

void DrawAnaNote(){
  
  gROOT->ForceStyle();
  
  TStyle* style = new TStyle("Default","Default style");
  style->SetTitleSize(0.05,"X");
  style->SetTitleSize(0.05,"Y");
  style->SetTitleOffset(0.9,"Y");
  style->SetTitleOffset(0.9,"X");
  style->SetFrameLineWidth(2);
  style->SetFrameFillColor(0);
  style->SetPadColor(0);
  style->SetLabelSize(0.03,"X");
  style->SetLabelSize(0.03,"Y");
  style->SetPadTopMargin(0.1);
  style->SetPadBottomMargin(0.15);
  style->SetPadLeftMargin(0.15);
  style->SetPadTopMargin(0.02);
  style->SetPadRightMargin(0.02);
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
  
  TFile* in_flow_file[n_energy][n_sorts];
  TFile* in_res_true_file[n_energy];
  TFile* in_res_reco_file[n_energy];
  
  TH1F*     h_pt_reco_in_before[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_pt_true_in_before[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_pt_reco_in_after[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_pt_true_in_after[n_energy][n_centrality][n_sorts+1];
  
  TH1F*     h_eta_reco_in_before[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_eta_true_in_before[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_eta_reco_in_after[n_energy][n_centrality][n_sorts+1];
  TH1F*     h_eta_true_in_after[n_energy][n_centrality][n_sorts+1];
  
  TH1F*     h_pt_reco_before[n_energy][n_sorts+1];
  TH1F*     h_pt_true_before[n_energy][n_sorts+1];
  TH1F*     h_pt_reco_after[n_energy][n_sorts+1];
  TH1F*     h_pt_true_after[n_energy][n_sorts+1];
  
  TH1F*     h_eta_reco_before[n_energy][n_sorts+1];
  TH1F*     h_eta_true_before[n_energy][n_sorts+1];
  TH1F*     h_eta_reco_after[n_energy][n_sorts+1];
  TH1F*     h_eta_true_after[n_energy][n_sorts+1];
  
  TH1F*     h_pt_eff_before[n_energy][n_sorts+1];
  TH1F*     h_pt_eff_after[n_energy][n_sorts+1];
  TH1F*     h_eta_eff_before[n_energy][n_sorts+1];
  TH1F*     h_eta_eff_after[n_energy][n_sorts+1];
  
  TProfile* p_res_vs_centrality[n_energy][n_harm];
  TH1F*     h_res_vs_centrality[n_energy][n_harm];
  
  TH1F*     h_n_hits_before[n_energy];
  TH1F*     h_n_hits_after[n_energy];
  
  in_res_true_file[0] = new TFile("/home/peter/res_hist-11gev.root","read");
  in_res_reco_file[0] = new TFile("/home/peter/res-fit-11gev.root","read");
  in_flow_file[0][0] = new TFile("/home/peter/flow-11gev-protons_noBirkPDG.root","read");
  in_flow_file[0][1] = new TFile("/home/peter/flow-11gev-kaons_noBirkPDG.root","read");
  in_flow_file[0][2] = new TFile("/home/peter/flow-11gev-pions_noBirkPDG.root","read");
  
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    h_n_hits_before[i_energy] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_nhits_TPC"));
    h_n_hits_before[i_energy]->SetName(Form("h_n_hits_before%i",i_energy));
    h_n_hits_after[i_energy] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_nhits_TPC_after"));
    h_n_hits_after[i_energy]->SetName(Form("h_n_hits_after%i",i_energy));
    for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
      h_pt_reco_before[i_energy][i_sort] = new TH1F(Form("h_pt_reco_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
      h_pt_true_before[i_energy][i_sort] = new TH1F(Form("h_pt_true_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
      h_pt_reco_after[i_energy][i_sort] = new TH1F(Form("h_pt_reco_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
      h_pt_true_after[i_energy][i_sort] = new TH1F(Form("h_pt_true_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
      
      h_eta_reco_before[i_energy][i_sort] = new TH1F(Form("h_eta_reco_before%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);
      h_eta_true_before[i_energy][i_sort] = new TH1F(Form("h_eta_true_before%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);
      h_eta_reco_after[i_energy][i_sort] = new TH1F(Form("h_eta_reco_after%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);
      h_eta_true_after[i_energy][i_sort] = new TH1F(Form("h_eta_true_after%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);

      h_pt_eff_before[i_energy][i_sort] = new TH1F(Form("h_pt_eff_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;Efficiency;"),100,0.,3.5);
      h_pt_eff_after[i_energy][i_sort] = new TH1F(Form("h_pt_eff_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;Efficiency;"),100,0.,3.5);
      
      h_eta_eff_before[i_energy][i_sort] = new TH1F(Form("h_eta_eff_before%i%i",i_energy,i_sort),Form(" ;#eta;Efficiency;"),100,-2.,2.);
      h_eta_eff_after[i_energy][i_sort] = new TH1F(Form("h_eta_eff_after%i%i",i_energy,i_sort),Form(" ;#eta;Efficiency;"),100,-2.,2.);
    }
    
    for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
      for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
        h_pt_reco_in_before[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_pt[%i][%i]",i_cent,i_sort));
        h_pt_reco_in_before[i_energy][i_cent][i_sort]->SetName(Form("h_pt_reco_in_before%i%i%i",i_energy,i_cent,i_sort));
        h_pt_true_in_before[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_pt_mc[%i][%i]",i_cent,i_sort));
        h_pt_true_in_before[i_energy][i_cent][i_sort]->SetName(Form("h_pt_true_in_before%i%i%i",i_energy,i_cent,i_sort));
        h_pt_reco_in_after[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_pt_after[%i][%i]",i_cent,i_sort));
        h_pt_reco_in_after[i_energy][i_cent][i_sort]->SetName(Form("h_pt_reco_in_after%i%i%i",i_energy,i_cent,i_sort));
        h_pt_true_in_after[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_pt_mc_after[%i][%i]",i_cent,i_sort));
        h_pt_true_in_after[i_energy][i_cent][i_sort]->SetName(Form("h_pt_true_in_after%i%i%i",i_energy,i_cent,i_sort));

        h_eta_reco_in_before[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta[%i][%i]",i_cent,i_sort));
        h_eta_reco_in_before[i_energy][i_cent][i_sort]->SetName(Form("h_eta_reco_in_before%i%i%i",i_energy,i_cent,i_sort));
        h_eta_true_in_before[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta_mc[%i][%i]",i_cent,i_sort));
        h_eta_true_in_before[i_energy][i_cent][i_sort]->SetName(Form("h_eta_true_in_before%i%i%i",i_energy,i_cent,i_sort));
        h_eta_reco_in_after[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta_after[%i][%i]",i_cent,i_sort));
        h_eta_reco_in_after[i_energy][i_cent][i_sort]->SetName(Form("h_eta_reco_in_after%i%i%i",i_energy,i_cent,i_sort));
        h_eta_true_in_after[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta_mc_after[%i][%i]",i_cent,i_sort));
        h_eta_true_in_after[i_energy][i_cent][i_sort]->SetName(Form("h_eta_true_in_after%i%i%i",i_energy,i_cent,i_sort));
      }
    }
    for (Int_t i_harm=0; i_harm<n_harm; i_harm++){
      p_res_vs_centrality[i_energy][i_harm] = (TProfile*) in_res_true_file[i_energy]->Get(Form("p_true_Res_vs_b[%i][%i][%i]",i_harm,0,1));
      p_res_vs_centrality[i_energy][i_harm]->SetName(Form("p_res_vs_centrality%i%i",i_energy,i_harm));
      h_res_vs_centrality[i_energy][i_harm] = (TH1F*)     in_res_reco_file[i_energy]->Get(Form("p_ResPsi_vs_b[%i][%i][%i]",i_harm,0,1));
      h_res_vs_centrality[i_energy][i_harm]->SetName(Form("h_res_vs_centrality%i%i",i_energy,i_harm));

      p_res_vs_centrality[i_energy][i_harm]->SetXTitle("Centrality, %");
      h_res_vs_centrality[i_energy][i_harm]->SetXTitle("Centrality, %");

      p_res_vs_centrality[i_energy][i_harm]->SetYTitle(Form("<cos[%i(#Psi_{%i}-#Psi_{RP})]>",i_harm+1,1));
      h_res_vs_centrality[i_energy][i_harm]->SetYTitle(Form("<cos[%i(#Psi_{%i}-#Psi_{RP})]>",i_harm+1,1));

      p_res_vs_centrality[i_energy][i_harm]->SetTitle("");
      h_res_vs_centrality[i_energy][i_harm]->SetTitle("");

      p_res_vs_centrality[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[0][i_energy]);
      h_res_vs_centrality[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[1][i_energy]);

      p_res_vs_centrality[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);
      h_res_vs_centrality[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);
    }
  }
  
  //N_HITS
  //--------------------------------------------------------------------------------------------------------
  TCanvas* c_hits[n_energy];
  TLegend* leg_hits_spectre[n_energy];
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    c_hits[i_energy] = new TCanvas(Form("c_hits%i",i_energy),Form("c_hits%i",i_energy),500,500);
    leg_hits_spectre[i_energy] = new TLegend(0.18,0.78,0.97,0.97);
    leg_hits_spectre[i_energy] -> SetHeader("Au-Au #sqrt{s_{NN}} = 11 GeV, UrQMD, GEANT3, 1M events","C");
    leg_hits_spectre[i_energy] -> AddEntry(h_n_hits_before[i_energy],"before selection","l");
    leg_hits_spectre[i_energy] -> AddEntry(h_n_hits_after[i_energy],"after selection","l");
    c_hits[i_energy] -> cd();
    c_hits[i_energy] -> SetLogy();
    h_n_hits_before[i_energy]->SetLineColor(marker_res_color[0]);
    h_n_hits_before[i_energy]->SetLineWidth(2);
    h_n_hits_after[i_energy]->SetLineColor(marker_res_color[1]);
    h_n_hits_after[i_energy]->SetLineWidth(2);
    h_n_hits_before[i_energy]-> GetYaxis() -> SetRangeUser(2e2,2e9);
    h_n_hits_before[i_energy]->SetTitle("");
    h_n_hits_before[i_energy]->Draw();
    h_n_hits_after[i_energy] -> Draw("same");
    leg_hits_spectre[i_energy] -> Draw();
    
    c_hits[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/HitSpectre%i.eps",i_energy),"recreate");
    c_hits[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/HitSpectre%i.pdf",i_energy),"recreate");
    c_hits[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/HitSpectre%i.png",i_energy),"recreate");
    c_hits[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/HitSpectre%i.C",i_energy),"recreate");
  }
  
  
  //EFFICIENCY
  //--------------------------------------------------------------------------------------------------------
  TCanvas* c_pt_eff         = new TCanvas("c_pt_eff","pt Efficiency",500,500);
  TCanvas* c_pt_eff_before  = new TCanvas("c_pt_eff_before","pt Efficiency before cuts",500,500);
  TLegend* leg_pt_eff       = new TLegend(0.45,0.24,0.89,0.55);
  TLegend* leg_pt_eff_before= new TLegend(0.14,0.55,0.58,0.9);
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
      for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
        h_pt_reco_before[i_energy][i_sort]->Add(h_pt_reco_in_before[i_energy][i_cent][i_sort]);
        h_pt_true_before[i_energy][i_sort]->Add(h_pt_true_in_before[i_energy][i_cent][i_sort]);
        h_pt_reco_after[i_energy][i_sort]->Add(h_pt_reco_in_after[i_energy][i_cent][i_sort]);
        h_pt_true_after[i_energy][i_sort]->Add(h_pt_true_in_after[i_energy][i_cent][i_sort]);
      }
    }
  }
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
      for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
          h_pt_eff_before[i_energy][i_sort]->Divide(h_pt_reco_before[i_energy][i_sort],h_pt_true_before[i_energy][i_sort]);
          h_pt_eff_after[i_energy][i_sort]->Divide(h_pt_reco_after[i_energy][i_sort],h_pt_true_after[i_energy][i_sort]);
      }
  }
  c_pt_eff->cd();
  h_pt_eff_after[0][2]->GetXaxis()->SetRangeUser(0,2.);
  h_pt_eff_after[0][2]->SetMarkerStyle(marker_flow_stl[0][1]);
  h_pt_eff_after[0][1]->SetMarkerStyle(marker_flow_stl[0][0]);
  h_pt_eff_after[0][3]->SetMarkerStyle(marker_flow_stl[0][2]);
  h_pt_eff_after[0][2]->SetMarkerColor(marker_res_color[1]);
  h_pt_eff_after[0][1]->SetMarkerColor(marker_res_color[0]);
  h_pt_eff_after[0][3]->SetMarkerColor(marker_res_color[2]);
  h_pt_eff_after[0][2]->Draw("P");
  h_pt_eff_after[0][1]->Draw("PSAME");
  h_pt_eff_after[0][3]->Draw("PSAME");
  leg_pt_eff->AddEntry(h_pt_eff_after[0][2],Form("Protons"),"p");
  leg_pt_eff->AddEntry(h_pt_eff_after[0][1],Form("Pions"),"p");
  leg_pt_eff->AddEntry(h_pt_eff_after[0][3],Form("Kaons"),"p");
  leg_pt_eff->Draw();

  c_pt_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiency.eps","recreate");
  c_pt_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiency.png","recreate");
  c_pt_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiency.pdf","recreate");
  c_pt_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiency.C","recreate");
  
  c_pt_eff_before -> cd();
  h_pt_eff_before[0][2]->GetXaxis()->SetRangeUser(0,2.);
  h_pt_eff_before[0][2]->SetMarkerStyle(marker_flow_stl[0][1]);
  h_pt_eff_before[0][1]->SetMarkerStyle(marker_flow_stl[0][0]);
  h_pt_eff_before[0][3]->SetMarkerStyle(marker_flow_stl[0][2]);
  h_pt_eff_before[0][2]->SetMarkerColor(marker_res_color[1]);
  h_pt_eff_before[0][1]->SetMarkerColor(marker_res_color[0]);
  h_pt_eff_before[0][3]->SetMarkerColor(marker_res_color[2]);
  h_pt_eff_before[0][2]->Draw("P");
  h_pt_eff_before[0][1]->Draw("PSAME");
  h_pt_eff_before[0][3]->Draw("PSAME");
  leg_pt_eff_before->AddEntry(h_pt_eff_before[0][2],Form("Protons"),"p");
  leg_pt_eff_before->AddEntry(h_pt_eff_before[0][1],Form("Pions"),"p");
  leg_pt_eff_before->AddEntry(h_pt_eff_before[0][3],Form("Kaons"),"p");
  leg_pt_eff_before->Draw();

  c_pt_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiencyBefore.eps","recreate");
  c_pt_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiencyBefore.png","recreate");
  c_pt_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiencyBefore.pdf","recreate");
  c_pt_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtEfficiencyBefore.C","recreate");
  
  
  TCanvas* c_eta_eff          = new TCanvas("c_eta_eff","eta Efficiency",500,500);
  TCanvas* c_eta_eff_before   = new TCanvas("c_eta_eff_before","eta Efficiency before cuts",500,500);
  TLegend* leg_eta_eff        = new TLegend(0.28,0.18,0.72,0.49);
  TLegend* leg_eta_eff_before = new TLegend(0.295,0.59,0.73,0.9);
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
      for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
        h_eta_reco_before[i_energy][i_sort]->Add(h_eta_reco_in_before[i_energy][i_cent][i_sort]);
        h_eta_true_before[i_energy][i_sort]->Add(h_eta_true_in_before[i_energy][i_cent][i_sort]);
        h_eta_reco_after[i_energy][i_sort]->Add(h_eta_reco_in_after[i_energy][i_cent][i_sort]);
        h_eta_true_after[i_energy][i_sort]->Add(h_eta_true_in_after[i_energy][i_cent][i_sort]);
      }
    }
  }

  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
      h_eta_eff_before[i_energy][i_sort]->Divide(h_eta_reco_before[i_energy][i_sort],h_eta_true_before[i_energy][i_sort]);
      h_eta_eff_after[i_energy][i_sort]->Divide(h_eta_reco_after[i_energy][i_sort],h_eta_true_after[i_energy][i_sort]);
    }
  }
  c_eta_eff->cd();
  h_eta_eff_after[0][2]->GetXaxis()->SetRangeUser(-2.,2.);
  h_eta_eff_after[0][2]->SetMarkerStyle(marker_flow_stl[0][1]);
  h_eta_eff_after[0][1]->SetMarkerStyle(marker_flow_stl[0][0]);
  h_eta_eff_after[0][3]->SetMarkerStyle(marker_flow_stl[0][2]);
  h_eta_eff_after[0][2]->SetMarkerColor(marker_res_color[1]);
  h_eta_eff_after[0][1]->SetMarkerColor(marker_res_color[0]);
  h_eta_eff_after[0][3]->SetMarkerColor(marker_res_color[2]);
  h_eta_eff_after[0][2]->Draw("P");
  h_eta_eff_after[0][1]->Draw("PSAME");
  h_eta_eff_after[0][3]->Draw("PSAME");
  leg_eta_eff->AddEntry(h_eta_eff_after[0][2],Form("Protons"),"p");
  leg_eta_eff->AddEntry(h_eta_eff_after[0][1],Form("Pions"),"p");
  leg_eta_eff->AddEntry(h_eta_eff_after[0][3],Form("Kaons"),"p");
  leg_eta_eff->Draw();

  c_eta_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiency.eps","recreate");
  c_eta_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiency.png","recreate");
  c_eta_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiency.pdf","recreate");
  c_eta_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiency.C","recreate");
  
  c_eta_eff_before->cd();
  h_eta_eff_before[0][2]->GetXaxis()->SetRangeUser(-2.,2.);
  h_eta_eff_before[0][2]->GetYaxis()->SetRangeUser(0.,2.2);
  h_eta_eff_before[0][2]->SetMarkerStyle(marker_flow_stl[0][1]);
  h_eta_eff_before[0][1]->SetMarkerStyle(marker_flow_stl[0][0]);
  h_eta_eff_before[0][3]->SetMarkerStyle(marker_flow_stl[0][2]);
  h_eta_eff_before[0][2]->SetMarkerColor(marker_res_color[1]);
  h_eta_eff_before[0][1]->SetMarkerColor(marker_res_color[0]);
  h_eta_eff_before[0][3]->SetMarkerColor(marker_res_color[2]);
  h_eta_eff_before[0][2]->Draw("P");
  h_eta_eff_before[0][1]->Draw("PSAME");
  h_eta_eff_before[0][3]->Draw("PSAME");
  leg_eta_eff_before->AddEntry(h_eta_eff_after[0][2],Form("Protons"),"p");
  leg_eta_eff_before->AddEntry(h_eta_eff_after[0][1],Form("Pions"),"p");
  leg_eta_eff_before->AddEntry(h_eta_eff_after[0][3],Form("Kaons"),"p");
  leg_eta_eff_before->Draw();

  c_eta_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiencyBefore.eps","recreate");
  c_eta_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiencyBefore.png","recreate");
  c_eta_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiencyBefore.pdf","recreate");
  c_eta_eff_before->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaEfficiencyBefore.C","recreate");
  
  //Tracks
  //--------------------------------------------------------------------------------------------------------
  
  TCanvas* c_pt[n_energy];
  TLegend* leg_pt_spectre[n_energy];
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    c_pt[i_energy] = new TCanvas(Form("c_pt%i",i_energy),Form("c_pt%i",i_energy),500,500);
    leg_pt_spectre[i_energy] = new TLegend(0.18,0.78,0.97,0.97);
    leg_pt_spectre[i_energy] -> SetHeader("Au-Au #sqrt{s_{NN}} = 11 GeV, UrQMD, GEANT3, 1M events","C");
    leg_pt_spectre[i_energy] -> AddEntry(h_pt_reco_before[i_energy][0],"before selection","l");
    leg_pt_spectre[i_energy] -> AddEntry(h_pt_reco_after[i_energy][0],"after selection","l");
    c_pt[i_energy] -> cd();
    c_pt[i_energy] -> SetLogy();
    h_pt_reco_before[i_energy][0]->SetLineColor(marker_res_color[0]);
    h_pt_reco_before[i_energy][0]->SetLineWidth(2);
    h_pt_reco_after[i_energy][0]->SetLineColor(marker_res_color[1]);
    h_pt_reco_after[i_energy][0]->SetLineWidth(2);
    h_pt_reco_before[i_energy][0]-> GetYaxis() -> SetRangeUser(2e2,2e9);
    h_pt_reco_before[i_energy][0]->SetTitle("");
    h_pt_reco_before[i_energy][0]->Draw();
    h_pt_reco_after[i_energy][0] -> Draw("same");
    leg_pt_spectre[i_energy]     -> Draw();
    
    c_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtSpectre%i.eps",i_energy),"recreate");
    c_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtSpectre%i.pdf",i_energy),"recreate");
    c_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtSpectre%i.png",i_energy),"recreate");
    c_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/PtSpectre%i.C",i_energy),"recreate");
  }
  
  TCanvas* c_eta[n_energy];
  TLegend* leg_eta_spectre[n_energy];
  for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
    c_eta[i_energy] = new TCanvas(Form("c_eta%i",i_energy),Form("c_eta%i",i_energy),500,500);
    leg_eta_spectre[i_energy] = new TLegend(0.18,0.78,0.97,0.97);
    leg_eta_spectre[i_energy] -> SetHeader("Au-Au #sqrt{s_{NN}} = 11 GeV, UrQMD, GEANT3, 1M events","C");
    leg_eta_spectre[i_energy] -> AddEntry(h_eta_reco_before[i_energy][0],"before selection","l");
    leg_eta_spectre[i_energy] -> AddEntry(h_eta_reco_after[i_energy][0],"after selection","l");
    c_eta[i_energy] -> cd();
    c_eta[i_energy] -> SetLogy();
    h_eta_reco_before[i_energy][0]->SetLineColor(marker_res_color[0]);
    h_eta_reco_before[i_energy][0]->SetLineWidth(2);
    h_eta_reco_after[i_energy][0]->SetLineColor(marker_res_color[1]);
    h_eta_reco_after[i_energy][0]->SetLineWidth(2);
    h_eta_reco_before[i_energy][0]-> GetYaxis() -> SetRangeUser(2e2,2e9);
    h_eta_reco_before[i_energy][0]->SetTitle("");
    h_eta_reco_before[i_energy][0]->Draw();
    h_eta_reco_after[i_energy][0] -> Draw("same");
    leg_eta_spectre[i_energy]     -> Draw();
    
    c_eta[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaSpectre%i.eps",i_energy),"recreate");
    c_eta[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaSpectre%i.pdf",i_energy),"recreate");
    c_eta[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaSpectre%i.png",i_energy),"recreate");
    c_eta[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/EtaSpectre%i.C",i_energy),"recreate");
  }
  
  TCanvas* c_pt_spectre_before[n_sorts+1];
  TCanvas* c_eta_spectre_before[n_sorts+1];
  TLegend* leg_pt_spectre_before[n_sorts+1];
  TLegend* leg_eta_spectre_before[n_sorts+1];
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_pt_spectre_before[i_sort]  = new TCanvas(Form("c_pt_spectre%i",i_sort),Form("pt spectre %i",i_sort),500,500);
    c_eta_spectre_before[i_sort] = new TCanvas(Form("c_eta_spectre%i",i_sort),Form("eta spectre %i",i_sort),500,500);
    leg_pt_spectre_before[i_sort] = new TLegend(0.56,0.7,0.97,0.97);
    leg_eta_spectre_before[i_sort] = new TLegend(0.56,0.7,0.97,0.97);
  }
  
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_pt_spectre_before[i_sort] -> cd();
    c_pt_spectre_before[i_sort] -> SetLogy();
    h_pt_true_before[0][i_sort]->GetXaxis()->SetRangeUser(0,3.5);
    h_pt_true_before[0][i_sort]->GetYaxis()->SetRangeUser(pt_spectreY[i_sort].first,pt_spectreY[i_sort].second);
    h_pt_true_before[0][i_sort]->SetMarkerStyle(marker_flow_stl[0][0]);
    h_pt_reco_before[0][i_sort]->SetMarkerStyle(marker_flow_stl[1][0]);
    h_pt_true_before[0][i_sort]->SetMarkerColor(marker_res_color[0]);
    h_pt_reco_before[0][i_sort]->SetMarkerColor(marker_res_color[1]);
    
    h_pt_true_before[0][i_sort]->Draw("P");
    h_pt_reco_before[0][i_sort]->Draw("PSAME");
    
    leg_pt_spectre_before[i_sort] ->AddEntry((TObject*) NULL, particle_name[i_sort].c_str(),"");
    leg_pt_spectre_before[i_sort] ->AddEntry(h_pt_true_before[0][i_sort], "true", "p");
    leg_pt_spectre_before[i_sort] ->AddEntry(h_pt_reco_before[0][i_sort], "reco", "p");
    leg_pt_spectre_before[i_sort] ->Draw();
    
    c_pt_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreBefore%i.eps",i_sort),"recreate");
    c_pt_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreBefore%i.png",i_sort),"recreate");
    c_pt_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreBefore%i.pdf",i_sort),"recreate");
    c_pt_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreBefore%i.C",i_sort),"recreate");
  }
  
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_eta_spectre_before[i_sort] -> cd();
    c_eta_spectre_before[i_sort] -> SetLogy();
    h_eta_true_before[0][i_sort]->GetXaxis()->SetRangeUser(-2.,2.);
    h_eta_true_before[0][i_sort]->GetYaxis()->SetRangeUser(eta_spectreY[i_sort].first,eta_spectreY[i_sort].second);
    h_eta_true_before[0][i_sort]->SetMarkerStyle(marker_flow_stl[0][0]);
    h_eta_reco_before[0][i_sort]->SetMarkerStyle(marker_flow_stl[1][0]);
    h_eta_true_before[0][i_sort]->SetMarkerColor(marker_res_color[0]);
    h_eta_reco_before[0][i_sort]->SetMarkerColor(marker_res_color[1]);
    
    h_eta_true_before[0][i_sort]->Draw("P");
    h_eta_reco_before[0][i_sort]->Draw("PSAME");
    
    leg_eta_spectre_before[i_sort] ->AddEntry((TObject*) NULL, particle_name[i_sort].c_str(),"");
    leg_eta_spectre_before[i_sort] ->AddEntry(h_eta_true_before[0][i_sort], "true", "p");
    leg_eta_spectre_before[i_sort] ->AddEntry(h_eta_reco_before[0][i_sort], "reco", "p");
    leg_eta_spectre_before[i_sort] ->Draw();
    
    c_eta_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreBefore%i.eps",i_sort),"recreate");
    c_eta_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreBefore%i.png",i_sort),"recreate");
    c_eta_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreBefore%i.pdf",i_sort),"recreate");
    c_eta_spectre_before[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreBefore%i.C",i_sort),"recreate");
  }
  
  TCanvas* c_pt_spectre_after[n_sorts+1];
  TCanvas* c_eta_spectre_after[n_sorts+1];
  TLegend* leg_pt_spectre_after[n_sorts+1];
  TLegend* leg_eta_spectre_after[n_sorts+1];
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_pt_spectre_after[i_sort]  = new TCanvas(Form("c_pt_spectre_after%i",i_sort),Form("pt spectre after cuts %i",i_sort),500,500);
    c_eta_spectre_after[i_sort] = new TCanvas(Form("c_eta_spectre_after%i",i_sort),Form("eta spectre after cuts %i",i_sort),500,500);
    leg_pt_spectre_after[i_sort] = new TLegend(0.56,0.7,0.97,0.97);
    leg_eta_spectre_after[i_sort] = new TLegend(0.56,0.7,0.97,0.97);
  }
  
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_pt_spectre_after[i_sort] -> cd();
    c_pt_spectre_after[i_sort] -> SetLogy();
    h_pt_true_after[0][i_sort]->GetXaxis()->SetRangeUser(0,3);
    h_pt_true_after[0][i_sort]->GetYaxis()->SetRangeUser(pt_spectreY[i_sort].first,pt_spectreY[i_sort].second);
    h_pt_true_after[0][i_sort]->SetMarkerStyle(marker_flow_stl[0][0]);
    h_pt_reco_after[0][i_sort]->SetMarkerStyle(marker_flow_stl[1][0]);
    h_pt_true_after[0][i_sort]->SetMarkerColor(marker_res_color[0]);
    h_pt_reco_after[0][i_sort]->SetMarkerColor(marker_res_color[1]);
    
    h_pt_true_after[0][i_sort]->Draw("P");
    h_pt_reco_after[0][i_sort]->Draw("PSAME");
    
    leg_pt_spectre_after[i_sort] ->AddEntry((TObject*) NULL, particle_name[i_sort].c_str(),"");
    leg_pt_spectre_after[i_sort] ->AddEntry(h_pt_true_after[0][i_sort], "true", "p");
    leg_pt_spectre_after[i_sort] ->AddEntry(h_pt_reco_after[0][i_sort], "reco", "p");
    leg_pt_spectre_after[i_sort] ->Draw();
    
    c_pt_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreAfter%i.eps",i_sort),"recreate");
    c_pt_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreAfter%i.png",i_sort),"recreate");
    c_pt_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreAfter%i.pdf",i_sort),"recreate");
    c_pt_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/ptSpectreAfter%i.C",i_sort),"recreate");
  }
  
  for (int i_sort=0; i_sort<n_sorts+1;i_sort++){
    c_eta_spectre_after[i_sort] -> cd();
    c_eta_spectre_after[i_sort] -> SetLogy();
    h_eta_true_after[0][i_sort]->GetXaxis()->SetRangeUser(-2.,2.);
    h_eta_true_after[0][i_sort]->GetYaxis()->SetRangeUser(eta_spectreY[i_sort].first,eta_spectreY[i_sort].second);
    h_eta_true_after[0][i_sort]->SetMarkerStyle(marker_flow_stl[0][0]);
    h_eta_reco_after[0][i_sort]->SetMarkerStyle(marker_flow_stl[1][0]);
    h_eta_true_after[0][i_sort]->SetMarkerColor(marker_res_color[0]);
    h_eta_reco_after[0][i_sort]->SetMarkerColor(marker_res_color[1]);
    
    h_eta_true_after[0][i_sort]->Draw("P");
    h_eta_reco_after[0][i_sort]->Draw("PSAME");
    
    leg_eta_spectre_after[i_sort] ->AddEntry((TObject*) NULL, particle_name[i_sort].c_str(),"");
    leg_eta_spectre_after[i_sort] ->AddEntry(h_eta_true_after[0][i_sort], "true", "p");
    leg_eta_spectre_after[i_sort] ->AddEntry(h_eta_reco_after[0][i_sort], "reco", "p");
    leg_eta_spectre_after[i_sort] ->Draw();
    
    c_eta_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreAfter%i.eps",i_sort),"recreate");
    c_eta_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreAfter%i.png",i_sort),"recreate");
    c_eta_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreAfter%i.pdf",i_sort),"recreate");
    c_eta_spectre_after[i_sort] -> SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/etaSpectreAfter%i.C",i_sort),"recreate");
  }
  
  //RESOLUTION VS CENTRALITY
  //--------------------------------------------------------------------------------------------------------
  TCanvas* c_res0   = new TCanvas("c_res0","Resolution for v1",500,500);
  TCanvas* c_res1   = new TCanvas("c_res1","Resolution for v2",500,500);
  TLegend* leg_res;
  TLegend* leg_res_energy;

  leg_res = new TLegend(0.23,0.77,0.60,0.95);

  leg_res_energy = new TLegend(0.66,0.77,0.85,0.95);

  leg_res->AddEntry((TObject*)0,"UrQMD, GEANT3, 1M events","");
  leg_res->AddEntry((TObject*)0,"","");
  leg_res->AddEntry((TObject*)0,"","");
  //for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
      //leg_res->AddEntry(h_res_vs_centrality[i_energy][0],energy_title[i_energy].Data(),"p");
  //}
  //leg_res->AddEntry((TObject*)0,"LAQGSM Au+Au","");
  //leg_res->AddEntry(p_res_laqgsm_vs_centrality[0],energy_title[1].Data(),"l");
  leg_res_energy->SetHeader("Au-Au, 11 GeV");
  leg_res_energy->AddEntry(p_res_vs_centrality[0][0],"true","p");
  leg_res_energy->AddEntry(h_res_vs_centrality[0][0],"reco","p");

  for (Int_t i=0;i<2;i++){
      if (i==0)c_res0->cd();
      if (i==1)c_res1->cd();
      p_res_vs_centrality[0][i]->GetYaxis()->SetRangeUser(res_range[i][0],res_range[i][1]);
      p_res_vs_centrality[0][i]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
      p_res_vs_centrality[0][i]->Draw();
      h_res_vs_centrality[0][i]->Draw("PSAME,HIST");
      //p_res_vs_centrality[1][i]->Draw("SAME");
      //h_res_vs_centrality[1][i]->Draw("PSAME,HIST");
      //p_res_laqgsm_vs_centrality[i]->Draw("SAME");
      //h_res_laqgsm_vs_centrality[i]->Draw("SAME");
      leg_res_energy->Draw();
      leg_res->Draw();
      //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
  }
  c_res0->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v1_vs_centrality.eps","recreate");
  c_res0->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v1_vs_centrality.png","recreate");
  c_res0->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v1_vs_centrality.pdf","recreate");
  c_res0->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v1_vs_centrality.C","recreate");
  c_res1->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v2_vs_centrality.eps","recreate");
  c_res1->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v2_vs_centrality.png","recreate");
  c_res1->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v2_vs_centrality.pdf","recreate");
  c_res1->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/AnaNote/res_v2_vs_centrality.C","recreate");
  
}
