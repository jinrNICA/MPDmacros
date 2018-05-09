#define PID // PDG of PID

const Int_t n_harm       = 2;
const Int_t n_sorts      = 3;
const Int_t n_centrality = 2;
const Int_t marker_res_color[]={1,2,4,2};
const Int_t marker_res_style[]={24,20,26,22};
const Int_t marker_flow_stl[2][3] ={{20,21,22},{24,25,26}};
const Float_t range_vn_pt[2][2][2]      ={{{-0.045,0.078},{-0.045,0.078}},{{0.,0.099},{0.,0.099}}};
const Float_t pt_range[]             ={0.21,2.};
const Float_t res_range[2][2]        ={{0.21,1.19},{0.01,0.96}};
const Int_t   centrality_range[]     ={0,79};
const TString vn_Title[]        = {TString("Au-Au, #sqrt{s_{NN}}=11 GeV, 10-20%, GEANT3, UrQMD"), TString("Au-Au, #sqrt{s_{NN}}=11 GeV, 10-20%, GEANT3, UrQMD")};
const TString vn_tracking[]        = {TString("RECO"), TString("TRUE")};
const int     canv_id[]         = {2,4,1,3};
const double                   padMarginX = 0.11;
const double                   padMarginY = 0.11;
const double                   padMarginXmin = 0.025;
const double                   padMarginYmin = 0.0;
//const std::pair<double,double> padX [] = {{0.,(1.-padMarginX)/2.+padMarginX},
                                          //{(1.-padMarginX)/2.+padMarginX,1.},
                                          //{0.,(1.-padMarginX)/2.+padMarginX},
                                          //{(1.-padMarginX)/2.+padMarginX,1.}};
                                          
const std::pair<double,double> padX [] = {{0.,(1.-0.)/2.+0.},
                                          {(1.-0.)/2.+0.,1.},
                                          {0.,(1.-0.)/2.+0.},
                                          {(1.-0.)/2.+0.,1.}};
                                          
const std::pair<double,double> padY [] = {{(1.-padMarginY)/2.+padMarginY,1.},
                                          {(1.-padMarginY)/2.+padMarginY,1.},
                                          {0.,(1.-padMarginY)/2.+padMarginY},
                                          {0.,(1.-padMarginY)/2.+padMarginY}};
                                          
const double padMargins [4][4]         = {{padMarginYmin,padMarginXmin,( 1/( (1.-padMarginY)/2.+padMarginY ) )*padMarginYmin,( 1/( (1.-padMarginX)/2.+padMarginX ) )*padMarginX},
                                          {padMarginYmin,padMarginXmin,( 1/( (1.-padMarginY)/2.+padMarginY ) )*padMarginYmin,( 1/( (1.-padMarginX)/2.+padMarginX ) )*padMarginX},
                                          {padMarginYmin,padMarginXmin,( 1/( (1.-padMarginY)/2.+padMarginY ) )*padMarginY   ,( 1/( (1.-padMarginX)/2.+padMarginX ) )*padMarginX},
                                          {padMarginYmin,padMarginXmin,( 1/( (1.-padMarginY)/2.+padMarginY ) )*padMarginY   ,( 1/( (1.-padMarginX)/2.+padMarginX ) )*padMarginX}};
void DrawRecoComparison()
{
  gROOT->ForceStyle();
  
  char name[200];
  char title[200];
  
  TFile* in_flow_file[2][3];
  TFile* in_res_true_file[2];
  TFile* in_res_reco_file[2];
  
  in_res_true_file[0] = new TFile("/home/peter/res_hist-11gev-4M.root","read");
  in_res_true_file[1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-11-gev.root","read");
  in_res_reco_file[0] = new TFile("/home/peter/res-fit-11gev-4M.root","read");
  in_res_reco_file[1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-fit-11-gev.root","read");
  
  #ifdef PDG
  in_flow_file[0][0] = new TFile("/home/peter/flow-11gev-protons4MPDG.root","read");
  in_flow_file[0][1] = new TFile("/home/peter/flow-11gev-kaons4MPDG.root","read");
  in_flow_file[0][2] = new TFile("/home/peter/flow-11gev-pions4MPDG.root","read");
  #endif
  #ifdef PID
  in_flow_file[0][0] = new TFile("/home/peter/flow-11gev-protons4M.root","read");
  in_flow_file[0][1] = new TFile("/home/peter/flow-11gev-kaons4M.root","read");
  in_flow_file[0][2] = new TFile("/home/peter/flow-11gev-pions4M.root","read");
  #endif
  in_flow_file[1][0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-proton.root","read");
  in_flow_file[1][1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-kaon.root","read");
  in_flow_file[1][2] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-pion.root","read");
  
  TFile* inStyle = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/my_style.root","READ");
    
  TStyle* style = (TStyle*) inStyle->Get("style");
  
  style->cd();
    
  gStyle->SetPalette(1);
  
  TProfile* p_vn_true_vs_pt[2][n_harm][n_centrality][n_sorts];
  TProfile* p_vn_reco_vs_pt[2][n_harm][n_centrality][n_sorts];
  
  TProfile* p_res_vs_centrality[2][n_harm];
  TH1F*     h_res_vs_centrality[2][n_harm];
  
  for (int i=0;i<2;i++){
    for (Int_t i_harm=0; i_harm<n_harm; i_harm++){
      
      p_res_vs_centrality[i][i_harm] = (TProfile*) in_res_true_file[i]->Get(Form("p_true_Res_vs_b[%i][%i][%i]",i_harm,0,1));
      p_res_vs_centrality[i][i_harm]->SetName(Form("p_res_vs_centrality%i%i",i,i_harm));
      h_res_vs_centrality[i][i_harm] = (TH1F*)     in_res_reco_file[i]->Get(Form("p_ResPsi_vs_b[%i][%i][%i]",i_harm,0,1));
      h_res_vs_centrality[i][i_harm]->SetName(Form("h_res_vs_centrality%i%i",i,i_harm));
      
      p_res_vs_centrality[i][i_harm]->SetXTitle("Centrality, %");
      h_res_vs_centrality[i][i_harm]->SetXTitle("Centrality, %");
      p_res_vs_centrality[i][i_harm]->SetYTitle(Form("R_{%i} {#Psi_{EP,%i}}",i_harm+1,1));
      h_res_vs_centrality[i][i_harm]->SetYTitle(Form("R_{%i} {#Psi_{EP,%i}}",i_harm+1,1));
      p_res_vs_centrality[i][i_harm]->SetTitle("");
      h_res_vs_centrality[i][i_harm]->SetTitle("");
      p_res_vs_centrality[i][i_harm]->SetMarkerStyle(marker_flow_stl[i][0]);
      h_res_vs_centrality[i][i_harm]->SetMarkerStyle(marker_flow_stl[i][1]);
      p_res_vs_centrality[i][i_harm]->SetMarkerSize(1.1);
      h_res_vs_centrality[i][i_harm]->SetMarkerSize(1.1);
      p_res_vs_centrality[i][i_harm]->SetMarkerColor(marker_res_color[i]);
      h_res_vs_centrality[i][i_harm]->SetMarkerColor(marker_res_color[i]);
      
      for (Int_t i_sort=0;i_sort<n_sorts;i_sort++){
        for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort] = (TProfile*) in_flow_file[i][i_sort]->Get(Form("p_flow_wrt_full_vs_pt_divided[%i][%i][%i][%i]"      ,i_cent,i_harm,0,1));
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort] ->SetName(Form("p_vn_reco_vs_pt%i%i%i%i",i,i_harm,i_cent,i_sort));
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->GetYaxis()->SetRangeUser(range_vn_pt[i_harm][i_cent][0],range_vn_pt[i_harm][i_cent][1] );
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetYTitle(Form("v_{%i}",i_harm+1));
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetTitle("");
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetXTitle("p_{T}, GeV/c");
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerStyle(marker_flow_stl[i][i_sort]);
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerSize(1.1);
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerColor(marker_res_color[i_sort]);
          p_vn_reco_vs_pt[i][i_harm][i_cent][i_sort]       ->SetLineColor(marker_res_color[i_sort]);
          
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort] = (TProfile*) in_flow_file[i][i_sort]->Get(Form("p_flow_wrt_RP_vs_pt[%i][%i]"      ,i_cent,i_harm));
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort] ->SetName(Form("p_vn_true_vs_pt%i%i%i%i",i,i_harm,i_cent,i_sort));
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->GetYaxis()->SetRangeUser(range_vn_pt[i_harm][i_cent][0],range_vn_pt[i_harm][i_cent][1] );
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetYTitle(Form("v_{%i}",i_harm+1));
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetTitle("");
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetXTitle("p_{T}, GeV/c");
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerStyle(marker_flow_stl[i][i_sort]);
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerSize(1.1);
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetMarkerColor(marker_res_color[i_sort]);
          p_vn_true_vs_pt[i][i_harm][i_cent][i_sort]       ->SetLineColor(marker_res_color[i_sort]);
        }
      }
    }
  }
  
  //RESOLUTION VS CENTRALITY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_res   = new TCanvas("c_res","Resolution",1000,1000);
    TLegend* leg_res[2];
    TLegendEntry *headerRes;
    for (int i=0;i<2;i++){
      leg_res[i] = new TLegend(0.25,0.85,0.95,0.98);
      leg_res[i]->SetHeader("Au-Au, #sqrt{s_{NN}}=11 GeV, UrQMD, GEANT3","C");
      leg_res[i]->SetNColumns(2);
      headerRes = (TLegendEntry*)leg_res[i]->GetListOfPrimitives()->First();
      headerRes->SetTextSize(.033);
    }
    
    leg_res[0]->AddEntry(p_res_vs_centrality[0][0],"new true","p");
    leg_res[0]->AddEntry(p_res_vs_centrality[1][0],"old true","p");
    leg_res[1]->AddEntry(h_res_vs_centrality[0][0],"new reco","p");
    leg_res[1]->AddEntry(h_res_vs_centrality[1][0],"old reco","p");

    c_res->Divide(2,2);

    for (Int_t i=0;i<2;i++){
        c_res->cd(canv_id[i]);
        p_res_vs_centrality[0][i]->GetYaxis()->SetRangeUser(res_range[i][0],res_range[i][1]);
        p_res_vs_centrality[0][i]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        p_res_vs_centrality[0][i]->GetYaxis()->SetNdivisions(5);
        p_res_vs_centrality[0][i]       ->SetMarkerSize(1.4);
        p_res_vs_centrality[0][i]->Draw();
        p_res_vs_centrality[1][i]->Draw("PSAME,HIST");
        //h_res_vs_centrality[0][i]->Draw("PSAME,HIST");
        //p_res_vs_centrality[1][i]->Draw("SAME");
        //h_res_vs_centrality[1][i]->Draw("PSAME,HIST");
        leg_res[0]->Draw();
        //leg_res_energy->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        c_res->cd(canv_id[i+2]);
        h_res_vs_centrality[0][i]->GetYaxis()->SetRangeUser(res_range[i][0],res_range[i][1]);
        h_res_vs_centrality[0][i]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        h_res_vs_centrality[0][i]->GetYaxis()->SetNdivisions(5);
        h_res_vs_centrality[0][i]       ->SetMarkerSize(1.4);
        h_res_vs_centrality[0][i]->Draw("PHIST");
        h_res_vs_centrality[1][i]->Draw("PSAME,HIST");
        //h_res_vs_centrality[0][i]->Draw("PSAME,HIST");
        //p_res_vs_centrality[1][i]->Draw("SAME");
        //h_res_vs_centrality[1][i]->Draw("PSAME,HIST");
        leg_res[1]->Draw();
        //leg_res_energy->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    }
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Comparison_res_vs_centrality.eps","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Comparison_res_vs_centrality.png","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Comparison_res_vs_centrality.pdf","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Comparison_res_vs_centrality.C","recreate");
  
  //VN VS PT
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_vn_pt[2];
    TLegend* leg_vn_pt[2][4];
    TLegend* leg_vn_type[2][4];
    TLegendEntry *headerPt;
    TLine*   line = new TLine();
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    
    TPad* pad[2][4];

    for (Int_t i_energy=0; i_energy<2; i_energy++){
        for (Int_t i=0;i<4;i++){
            leg_vn_pt[i_energy][i] = new TLegend(0.25,0.73,0.95,0.98);
            leg_vn_type[i_energy][i] = new TLegend(0.58,0.25,0.88,0.35);
            pad[i_energy][i] = new TPad(Form("pad%i%i",i_energy,i),Form("pad%i%i",i_energy,i),padX[i].first,padY[i].first,padX[i].second,padY[i].second);
            
            pad[i_energy][i]->SetTopMargin(    padMargins[i][0]);
            pad[i_energy][i]->SetRightMargin(  padMargins[i][1]);
            pad[i_energy][i]->SetBottomMargin( padMargins[i][2]);
            pad[i_energy][i]->SetLeftMargin(   padMargins[i][3]);
        }
    }

    for (Int_t i_energy=0; i_energy<2-1;i_energy++){

        c_vn_pt[i_energy] = new TCanvas(Form("c_vn_pt%i",i_energy),Form("vn vs pt %i", i_energy),900,700);
        c_vn_pt[i_energy]->cd();
        for (int i=0;i<4;i++){
          pad[i_energy][i] -> Draw();
        }
        //c_vn_pt[i_energy]-> Divide(2,2);
        //c_vn_pt[i_energy]->cd(2);
        pad[i_energy][1]->cd();
        leg_vn_pt[i_energy][0]->SetHeader(vn_Title[0].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][0]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][0]->SetNColumns(2);
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy+1][0][0][0],"old reco"     ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"new reco"     ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][0]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][0][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][0][0][0]->GetXaxis()->SetNdivisions(505);
        p_vn_reco_vs_pt[i_energy][0][0][0]->GetYaxis()->SetNdivisions(509);
        p_vn_reco_vs_pt[i_energy][0][0][0]->Draw();
        leg_vn_pt[i_energy][0]->Draw();
        p_vn_reco_vs_pt[i_energy][0][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][0][2]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][0][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][0][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][0][0][2]->Draw("SAME");
        line->DrawLine(pt_range[0],0.,pt_range[1],0.);
        leg_vn_type[i_energy][0]->SetHeader("10-20%");
        leg_vn_type[i_energy][0]->SetNColumns(3);
        leg_vn_type[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0]," p"        ,"p");
        leg_vn_type[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1]," K^{+}"    ,"p");
        leg_vn_type[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2]," #pi^{+}"  ,"p");
        //TLegendEntry *headerPt = (TLegendEntry*)leg_vn_type[i_energy][0]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_type[i_energy][0]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        //c_vn_pt[i_energy]->cd(4);
        //pad[i_energy][3]->cd();
        //leg_vn_pt[i_energy][1]->SetHeader(vn_Title[1].Data(),"C");
        //headerPt = (TLegendEntry*)leg_vn_pt[i_energy][1]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.028);
        //leg_vn_pt[i_energy][1]->SetNColumns(2);
        //leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        //leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy+1][0][0][0],"old true"     ,"p");
        //leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        //leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"new true"     ,"p");
        //leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        //leg_vn_pt[i_energy][1]->AddEntry((TObject*)0,"","");
        //p_vn_true_vs_pt[i_energy][0][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        //p_vn_true_vs_pt[i_energy][0][0][0]->GetXaxis()->SetNdivisions(5);
        //p_vn_true_vs_pt[i_energy][0][0][0]->Draw();
        //leg_vn_pt[i_energy][1]->Draw();
        //p_vn_true_vs_pt[i_energy][0][0][0]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy][0][0][1]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy][0][0][2]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][0][0][0]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][0][0][1]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][0][0][2]->Draw("SAME");
        //line->DrawLine(pt_range[0],0.,pt_range[1],0.);
        //leg_vn_type[i_energy][1]->SetHeader("20-40%");
        //leg_vn_type[i_energy][1]->SetNColumns(3);
        //leg_vn_type[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0]," p"        ,"p");
        //leg_vn_type[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][1]," K^{+}"    ,"p");
        //leg_vn_type[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][2]," #pi^{+}"  ,"p");
        //headerPt = (TLegendEntry*)leg_vn_type[i_energy][1]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_pt[i_energy]->SetHeader(Form("Au-Au, #sqrt{s_{NN}}=11 GeV, 20-40%, GEANT3, UrQMD, 4M events","C"));
        //leg_vn_type[i_energy][1]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        //c_vn_pt[i_energy]->cd(1);
        pad[i_energy][0]->cd();
        h_res_vs_centrality[0][0]->GetYaxis()->SetRangeUser(res_range[0][0],res_range[0][1]);
        h_res_vs_centrality[0][0]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        h_res_vs_centrality[0][0]->GetYaxis()->SetNdivisions(505);
        h_res_vs_centrality[0][0]       ->SetMarkerSize(1.4);
        h_res_vs_centrality[0][0]->Draw("PHIST");
        leg_res[1]->Draw();
        h_res_vs_centrality[0][0]->Draw("PSAME,HIST");
        h_res_vs_centrality[1][0]->Draw("PSAME,HIST");
        pad[i_energy][3]->cd();
        leg_vn_pt[i_energy][2]->SetHeader(vn_Title[0].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][2]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][2]->SetNColumns(2);
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy+1][0][0][0],"old reco"     ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"new reco"     ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][2]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][1][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][1][0][0]->GetXaxis()->SetNdivisions(505);
        p_vn_reco_vs_pt[i_energy][1][0][0]->GetYaxis()->SetNdivisions(509);
        p_vn_reco_vs_pt[i_energy][1][0][0]->Draw();
        //leg_vn_pt[i_energy][2]->Draw();
        p_vn_reco_vs_pt[i_energy][1][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][0][2]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][1][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][1][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy+1][1][0][2]->Draw("SAME");
        leg_vn_type[i_energy][2]->SetHeader("10-20%");
        leg_vn_type[i_energy][2]->SetNColumns(3);
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][0]," p"        ,"p");
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][1]," K^{+}"    ,"p");
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][2]," #pi^{+}"  ,"p");
        //headerPt = (TLegendEntry*)leg_vn_type[i_energy][2]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_type[i_energy][2]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        //c_vn_pt[i_energy]->cd(3);
        pad[i_energy][2]->cd();
        h_res_vs_centrality[0][1]->GetYaxis()->SetRangeUser(res_range[1][0],res_range[1][1]);
        h_res_vs_centrality[0][1]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        h_res_vs_centrality[0][1]->GetYaxis()->SetNdivisions(505);
        h_res_vs_centrality[0][1]       ->SetMarkerSize(1.4);
        h_res_vs_centrality[0][1]->Draw("PHIST");
        //leg_res[1]->Draw();
        h_res_vs_centrality[0][1]->Draw("PSAME,HIST");
        h_res_vs_centrality[1][1]->Draw("PSAME,HIST");
        //leg_vn_pt[i_energy][3]->SetHeader(vn_Title[1].Data(),"C");
        //headerPt = (TLegendEntry*)leg_vn_pt[i_energy][3]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.028);
        //leg_vn_pt[i_energy][3]->SetNColumns(2);
        //leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        //leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy+1][0][0][0],"old true"     ,"p");
        //leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        //leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"new true"     ,"p");
        //leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        //leg_vn_pt[i_energy][3]->AddEntry((TObject*)0,"","");
        //p_vn_true_vs_pt[i_energy][1][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        //p_vn_true_vs_pt[i_energy][1][0][0]->GetXaxis()->SetNdivisions(5);
        //p_vn_true_vs_pt[i_energy][1][0][0]->Draw();
        //leg_vn_pt[i_energy][3]->Draw();
        //p_vn_true_vs_pt[i_energy][1][0][0]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy][1][0][1]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy][1][0][2]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][1][0][0]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][1][0][1]->Draw("SAME");
        //p_vn_true_vs_pt[i_energy+1][1][0][2]->Draw("SAME");
        //leg_vn_type[i_energy][3]->SetHeader("20-40%");
        //leg_vn_type[i_energy][3]->SetNColumns(3);
        //leg_vn_type[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][1][0][0]," p"        ,"p");
        //leg_vn_type[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][1][0][1]," K^{+}"    ,"p");
        //leg_vn_type[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][1][0][2]," #pi^{+}"  ,"p");
        ////headerPt = (TLegendEntry*)leg_vn_type[i_energy][3]->GetListOfPrimitives()->First();
        ////headerPt->SetTextSize(.035);
        ////leg_vn_type[i_energy][3]->Draw();
        ////text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        
        #ifdef PDG
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPDG_vn_vs_pt_%i.eps",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPDG_vn_vs_pt_%i.png",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPDG_vn_vs_pt_%i.pdf",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPDG_vn_vs_pt_%i.C",i_energy),"recreate");
        #endif
        #ifdef PID
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPID_vn_vs_pt_%i.eps",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPID_vn_vs_pt_%i.png",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPID_vn_vs_pt_%i.pdf",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/ComparisonPID_vn_vs_pt_%i.C",i_energy),"recreate");
        #endif
    }
  
}
