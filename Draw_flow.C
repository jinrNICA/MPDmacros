#define _N_SORTS 3
#define _N_TYPE 3
#define _N_CENT 2
#define _N_HARM 2


void Draw_flow()
{
    TFile* file_CF = new TFile("~/Desktop/output_dca_DCA_w_chi.root","read");
    //TFile* file_CF = new TFile("~/Documents/WorkLocal/MPD/RootFiles/out_merged_CF_new.root","read");
    //TFile* file_HP = new TFile("~/Documents/WorkLocal/MPD/RootFiles/out_merged_HP_new.root","read");
    TFile* file_HP = new TFile("~/Desktop/output_dca_motherID_w_chi.root","read");
    //TFile* file_HP = new TFile("~/Desktop/output_dca_with_motherID_without_chi2vertex.root","read");
    
    TFile* file_CF_old = new TFile("~/Documents/WorkLocal/MPD/RootFiles/out_merged_CF.root","read");
    //TFile* file_HP = new TFile("~/Documents/WorkLocal/MPD/RootFiles/out_merged_HP.root","read");
    
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    gStyle->SetFrameLineWidth(2);
    
    const TString particle_sort[]={TString("Proton"),TString("Kaon"),TString("Pion")};
    const Float_t impact[]={2.,7.,12.};
    const Int_t   marker_style[]={20,25,26};
    const Int_t   marker_color[]={1,4,2};
    
    const float ptbin[] = {0.,0.2, 0.5, 0.8, 1.1, 1.4, 1.7, 2.0, 2.5, 3.0};
    const int   Nptbins = 9;
    
    TProfile* h_flow[_N_TYPE][_N_SORTS][_N_CENT][_N_HARM];
    TH1D* h_ratio[_N_TYPE-1][_N_SORTS][_N_CENT][_N_HARM];
    TH1D* proj[_N_TYPE][_N_SORTS][_N_CENT][_N_HARM];
    
    
    for (Int_t sort=0;sort<_N_SORTS;sort++){
        for (Int_t cent=0;cent<_N_CENT;cent++){
            for (Int_t harm=0;harm<_N_HARM;harm++){
                h_flow[0][sort][cent][harm] = (TProfile*) file_HP->Get(Form("p_flow_wrt_RP_vs_pt%i%i%i",sort,cent,harm));
                //h_flow[1][sort][cent][harm] = (TProfile*) file_CF_old->Get(Form("p_flow_wrt_full_vs_pt%i%i%i%i%i",sort,cent,harm,0,3));
                h_flow[1][sort][cent][harm] = (TProfile*) file_HP->Get(Form("p_flow_wrt_full_vs_pt%i%i%i%i%i",sort,cent,harm,0,3));
                h_flow[2][sort][cent][harm] = (TProfile*) file_CF->Get(Form("p_flow_wrt_full_vs_pt%i%i%i%i%i",sort,cent,harm,0,3));
                
                h_ratio[0][sort][cent][harm] = new TH1D(Form("h_ratio%i%i%i%i",0,sort,cent,harm),Form(""),Nptbins,ptbin);
                h_ratio[1][sort][cent][harm] = new TH1D(Form("h_ratio%i%i%i%i",1,sort,cent,harm),Form(""),Nptbins,ptbin);
                h_ratio[0][sort][cent][harm]->GetXaxis()->SetTitleSize(0.16);
                h_ratio[0][sort][cent][harm]->GetXaxis()->SetLabelSize(0.12);
                h_ratio[0][sort][cent][harm]->GetXaxis()->SetTitle("p_{T}, GeV/c");
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetTitleSize(0.16);
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetTitleOffset(0.4);
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetLabelSize(0.12);
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetTitle(Form("Reco/Gen",harm+1));
                
                h_ratio[0][sort][cent][harm]->SetMarkerStyle(marker_style[1]);
                h_ratio[0][sort][cent][harm]->SetMarkerColor(marker_color[1]);
                h_ratio[0][sort][cent][harm]->SetLineColor(marker_color[1]);
                h_ratio[0][sort][cent][harm]->SetMarkerSize(1.);
                h_ratio[0][sort][cent][harm]->SetLineWidth(3);
                
                h_ratio[1][sort][cent][harm]->SetMarkerStyle(marker_style[2]);
                h_ratio[1][sort][cent][harm]->SetMarkerColor(marker_color[2]);
                h_ratio[1][sort][cent][harm]->SetLineColor(marker_color[2]);
                h_ratio[1][sort][cent][harm]->SetMarkerSize(1.);
                h_ratio[1][sort][cent][harm]->SetLineWidth(3);
                
                h_ratio[0][sort][cent][harm]->Sumw2();
                h_ratio[1][sort][cent][harm]->Sumw2();
            }
        }
    }
    
    TCanvas* canv[_N_SORTS][_N_CENT][_N_HARM];
    TPad*    pad[2][_N_SORTS][_N_CENT][_N_HARM];
    TLegend* leg;
    TLine*   line = new TLine();
    line->SetLineWidth(3.);
    line->SetLineStyle(2);
    for (Int_t sort=0;sort<_N_SORTS;sort++){
        for (Int_t cent=0;cent<_N_CENT;cent++){
            for (Int_t harm=0;harm<_N_HARM;harm++){
                canv[sort][cent][harm] = new TCanvas(Form("canv%i%i%i",sort,cent,harm),Form("canv%i%i%i",sort,cent,harm),700,700);
                canv[sort][cent][harm]->cd();
                //canv[sort][cent][harm]->SetBottomMargin(0.17);
                //canv[sort][cent][harm]->SetLeftMargin(0.13);
                pad[0][sort][cent][harm] = new TPad(Form("pad%i%i%i%i",0,sort,cent,harm),Form("pad%i%i%i%i",0,sort,cent,harm),0.,0.33,1.,1.,0.,0.,0.);
                pad[0][sort][cent][harm]->SetBottomMargin(0);
                pad[0][sort][cent][harm]->SetLeftMargin(0.13);
                pad[0][sort][cent][harm]->SetTicks(1,1);
                pad[0][sort][cent][harm]->SetFixedAspectRatio();
                pad[0][sort][cent][harm]->Draw();
                pad[1][sort][cent][harm] = new TPad(Form("pad%i%i%i%i",0,sort,cent,harm),Form("pad%i%i%i%i",0,sort,cent,harm),0.,0.,1.,0.33,0.,0.,0.);
                pad[1][sort][cent][harm]->SetTopMargin(0);
                pad[1][sort][cent][harm]->SetLeftMargin(0.13);
                pad[1][sort][cent][harm]->SetBottomMargin(0.34);
                pad[1][sort][cent][harm]->SetTicks(1,1);
                pad[1][sort][cent][harm]->SetFixedAspectRatio();
                pad[1][sort][cent][harm]->Draw();
                leg = new TLegend(0.15,0.69,0.5,0.87);
                leg->SetBorderSize(0);
                
                h_flow[0][sort][cent][harm]->SetTitle(Form("%s at %1.1f < b < %1.1f fm",particle_sort[sort].Data(),impact[cent],impact[cent+1]));
                h_flow[0][sort][cent][harm]->GetXaxis()->SetTitleSize(0.08);
                h_flow[0][sort][cent][harm]->GetXaxis()->SetLabelSize(0.06);
                h_flow[0][sort][cent][harm]->GetXaxis()->SetTitle("p_{T}, GeV/c");
                h_flow[0][sort][cent][harm]->GetYaxis()->SetTitleSize(0.08);
                h_flow[0][sort][cent][harm]->GetYaxis()->SetTitleOffset(0.8);
                h_flow[0][sort][cent][harm]->GetYaxis()->SetLabelSize(0.06);
                h_flow[0][sort][cent][harm]->GetYaxis()->SetTitle(Form("v_{%i}",harm+1));
                if (harm==0) h_flow[0][sort][cent][harm]->GetYaxis()->SetRangeUser(-0.059,0.09);
                if (harm==1) h_flow[0][sort][cent][harm]->GetYaxis()->SetRangeUser(-0.019,0.14);
                h_flow[0][sort][cent][harm]->GetXaxis()->SetRangeUser(0.,2.48);
                
                h_flow[0][sort][cent][harm]->SetMarkerStyle(marker_style[0]);
                h_flow[0][sort][cent][harm]->SetMarkerColor(marker_color[0]);
                h_flow[0][sort][cent][harm]->SetLineColor(marker_color[0]);
                h_flow[0][sort][cent][harm]->SetMarkerSize(2.);
                h_flow[0][sort][cent][harm]->SetLineWidth(3);
                
                h_flow[1][sort][cent][harm]->SetMarkerStyle(marker_style[1]);
                h_flow[1][sort][cent][harm]->SetMarkerColor(marker_color[1]);
                h_flow[1][sort][cent][harm]->SetLineColor(marker_color[1]);
                h_flow[1][sort][cent][harm]->SetMarkerSize(2.);
                h_flow[1][sort][cent][harm]->SetLineWidth(3);
                
                h_flow[2][sort][cent][harm]->SetMarkerStyle(marker_style[2]);
                h_flow[2][sort][cent][harm]->SetMarkerColor(marker_color[2]);
                h_flow[2][sort][cent][harm]->SetLineColor(marker_color[2]);
                h_flow[2][sort][cent][harm]->SetMarkerSize(2.);
                h_flow[2][sort][cent][harm]->SetLineWidth(3);
                
                leg->AddEntry(h_flow[0][sort][cent][harm],"Gen","p");
                leg->AddEntry(h_flow[1][sort][cent][harm],"Reco, motherID","p");
                leg->AddEntry(h_flow[2][sort][cent][harm],"Reco, DCA","p");
                
                pad[0][sort][cent][harm]->cd();
                
                h_flow[0][sort][cent][harm]->Draw("X0");
                h_flow[1][sort][cent][harm]->Draw("X0,SAME");
                h_flow[2][sort][cent][harm]->Draw("X0,SAME");
                if (harm==0) line->DrawLine(0.,0.,2.5,0.);
                leg->Draw();
                
                pad[1][sort][cent][harm]->cd();
                
                proj[0][sort][cent][harm] = (TH1D*) h_flow[0][sort][cent][harm]->ProjectionX(); proj[0][sort][cent][harm]->Sumw2();
                proj[1][sort][cent][harm] = (TH1D*) h_flow[1][sort][cent][harm]->ProjectionX(); proj[1][sort][cent][harm]->Sumw2();
                proj[2][sort][cent][harm] = (TH1D*) h_flow[2][sort][cent][harm]->ProjectionX(); proj[2][sort][cent][harm]->Sumw2();
                
                h_ratio[0][sort][cent][harm]->Divide(proj[1][sort][cent][harm],proj[0][sort][cent][harm]);
                h_ratio[1][sort][cent][harm]->Divide(proj[2][sort][cent][harm],proj[0][sort][cent][harm]);
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetRangeUser(0.5,1.5);
                //h_ratio[0][sort][cent][harm]->GetYaxis()->SetRangeUser(0,4);
                h_ratio[0][sort][cent][harm]->GetXaxis()->SetRangeUser(0.,2.48);
                h_ratio[0][sort][cent][harm]->GetYaxis()->SetNdivisions(9);
                h_ratio[0][sort][cent][harm]->GetXaxis()->SetTickLength(0.06);
                h_ratio[0][sort][cent][harm]->Draw("X0");
                h_ratio[1][sort][cent][harm]->Draw("X0,SAME");
                line->DrawLine(0.,1.,2.5,1.);
                
                canv[sort][cent][harm]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Flow/v_%i_%s_%i.png",harm+1,particle_sort[sort].Data(),cent),"recreate");
                
            }
        }
    }
                
                
                
                
    
}
