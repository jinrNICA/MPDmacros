void Draw_DCA(){
    
    //TFile* file = new TFile("~/Desktop/dca_cut_file.root","read");
    //TFile* cutfile = new TFile("~/Desktop/dca_cut_file.root","read");
    
    TFile* file = new TFile("~/Desktop/dca_out_file_TDR.root","read");
    TFile* cutfile = new TFile("~/Desktop/dca_out_file_TDR.root","read");
    
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    gStyle->SetFrameLineWidth(2);
    
    const Int_t   marker_style[]={20,21,24,25};
    const Int_t   marker_color[]={1,4,2};
    
    const Float_t pt_bins[]={0.,0.2, 0.5, 0.8, 1.1, 1.4, 1.7, 2.0, 2.5, 3.0};
    const Float_t eta_bins[]={0.,0.5,1.0,1.5};
    const Int_t n_pt_bin = 9;
    const Int_t n_eta_bin = 3;
    const Int_t n_proj = 3;
    const Float_t pt_min = 0.2;
    const Int_t n_cut = 2;
    const TString s_proj[]={TString("x"),TString("y"),TString("z")};
    const TString s_DCA[]={TString("All"),TString("Primary"),TString("Secondary")};
    const TString s_cut[]={TString("no #chi^{2}_{v} cut"),TString("with #chi^{2}_{v} cut")};
    
    TH1F *h_dca_all[n_cut][n_proj][n_pt_bin][n_eta_bin];
    TH1F *h_dca_primary[n_cut][n_proj][n_pt_bin][n_eta_bin];
    TH1F *h_dca_secondary[n_cut][n_proj][n_pt_bin][n_eta_bin];    
    TH1F *h_dca_eff[n_cut][n_proj][n_pt_bin][n_eta_bin];
    TH1F *h_dca_cnt[n_cut][n_proj][n_pt_bin][n_eta_bin];
    
    TF1  *f_dca_all[n_cut][n_proj][n_pt_bin][n_eta_bin];
    TF1  *f_dca_primary[n_cut][n_proj][n_pt_bin][n_eta_bin];
    TF1  *f_dca_secondary[n_cut][n_proj][n_pt_bin][n_eta_bin]; 
    
    TH1F *h_chi2_vertex[n_cut][n_pt_bin][n_eta_bin];
    TH1F *h_chi2_NDF[n_cut][n_pt_bin][n_eta_bin];
    
    TH2F *h_DCA_chi2_NDF[3][n_cut][n_proj][n_pt_bin][n_eta_bin];
    TH2F *h_DCA_chi2_vertex[3][n_cut][n_proj][n_pt_bin][n_eta_bin];
    TH2F *h_chi2_NDF_vertex[n_cut][n_pt_bin][n_eta_bin];
    
    TH1F *pt_total[n_cut];
    TH1F *eta_total[n_cut];
    TH2F *eta_vs_n_hits_total[n_cut];
    TH2F *pt_vs_n_hits_total[n_cut];
    TH2F *mc_eta_vs_n_hits_total[n_cut];
    TH2F *mc_pt_vs_n_hits_total[n_cut];
    TH2F *eta_vs_NDF_total[n_cut];
    TH2F *pt_vs_NDF_total[n_cut];
    TH2F *pt_vs_eta_total[n_cut];
    TH2F *mc_pt_vs_eta_total[n_cut];
    TH1F *h_hits_mpd[n_cut];
    
    TH1F *I_DCA_all[n_cut][n_proj];
    TH1F *I_DCA_primary[n_cut][n_proj];
    TH1F *I_DCA_secondary[n_cut][n_proj];
    TH1F *I_DCA_eff[n_cut][n_proj];
    TH1F *I_DCA_cnt[n_cut][n_proj];
    
    TH1F *I_DCA_eta_all[n_cut][n_proj][n_eta_bin];
    TH1F *I_DCA_eta_primary[n_cut][n_proj][n_eta_bin];
    TH1F *I_DCA_eta_secondary[n_cut][n_proj][n_eta_bin];
    TH1F *I_DCA_eta_eff[n_cut][n_proj][n_eta_bin];
    TH1F *I_DCA_eta_cnt[n_cut][n_proj][n_eta_bin];
    
    TH1F *I_DCA_pt_all[n_cut][n_proj][n_pt_bin];
    TH1F *I_DCA_pt_primary[n_cut][n_proj][n_pt_bin];
    TH1F *I_DCA_pt_secondary[n_cut][n_proj][n_pt_bin];
    TH1F *I_DCA_pt_eff[n_cut][n_proj][n_pt_bin];
    TH1F *I_DCA_pt_cnt[n_cut][n_proj][n_pt_bin];
    
    for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
        pt_total[i_cut] = (TH1F*) file->Get(Form("pt_total%i",i_cut));
        eta_total[i_cut] = (TH1F*) file->Get(Form("eta_total%i",i_cut));
        eta_vs_n_hits_total[i_cut] = (TH2F*) file->Get(Form("eta_vs_n_hits_total%i",i_cut));
        pt_vs_n_hits_total[i_cut] = (TH2F*) file->Get(Form("pt_vs_n_hits_total%i",i_cut));
        mc_eta_vs_n_hits_total[i_cut] = (TH2F*) file->Get(Form("mc_eta_vs_n_hits_total%i",i_cut));
        mc_pt_vs_n_hits_total[i_cut] = (TH2F*) file->Get(Form("mc_pt_vs_n_hits_total%i",i_cut));
        eta_vs_NDF_total[i_cut] = (TH2F*) file->Get(Form("eta_vs_NDF_total%i",i_cut));
        pt_vs_NDF_total[i_cut] = (TH2F*) file->Get(Form("pt_vs_NDF_total%i",i_cut));
        pt_vs_eta_total[i_cut] = (TH2F*) file->Get(Form("pt_vs_eta_total%i",i_cut));
        mc_pt_vs_eta_total[i_cut] = (TH2F*) file->Get(Form("mc_pt_vs_eta_total%i",i_cut));
        h_hits_mpd[i_cut] = (TH1F*) file->Get(Form("h_hits_mpd%i",i_cut));
        
        pt_total[i_cut]->GetXaxis()->SetTitleSize(0.08);
        pt_total[i_cut]->GetXaxis()->SetLabelSize(0.06);
        pt_total[i_cut]->GetXaxis()->SetTitle(Form("p_{T}, GeV/c"));
        pt_total[i_cut]->GetYaxis()->SetTitleSize(0.08);
        pt_total[i_cut]->GetYaxis()->SetTitleOffset(0.8);
        pt_total[i_cut]->GetYaxis()->SetLabelSize(0.06);
        
        eta_total[i_cut]->GetXaxis()->SetTitleSize(0.08);
        eta_total[i_cut]->GetXaxis()->SetLabelSize(0.06);
        eta_total[i_cut]->GetXaxis()->SetTitle(Form("#eta"));
        eta_total[i_cut]->GetYaxis()->SetTitleSize(0.08);
        eta_total[i_cut]->GetYaxis()->SetTitleOffset(0.8);
        eta_total[i_cut]->GetYaxis()->SetLabelSize(0.06);
        
        for (Int_t i=0;i<n_proj;i++){
        
        I_DCA_all[i_cut][i] = new TH1F(Form("I_DCA_all%i%i",i_cut,i),Form("All DCA %s %s",s_cut[i_cut].Data(),s_proj[i].Data()),80,-10.,10.);
        I_DCA_primary[i_cut][i] = new TH1F(Form("I_DCA_primary%i%i",i_cut,i),Form("Primary DCA %s %s",s_cut[i_cut].Data(),s_proj[i].Data()),80,-10.,10.);
        I_DCA_secondary[i_cut][i] = new TH1F(Form("I_DCA_secondary%i%i",i_cut,i),Form("Secondary DCA %s %s",s_cut[i_cut].Data(),s_proj[i].Data()),80,-10.,10.);
        
        I_DCA_all[i_cut][i]->GetXaxis()->SetTitleSize(0.16);
        I_DCA_all[i_cut][i]->GetXaxis()->SetLabelSize(0.12);
        I_DCA_all[i_cut][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_all[i_cut][i]->GetYaxis()->SetTitleSize(0.16);
        I_DCA_all[i_cut][i]->GetYaxis()->SetTitleOffset(0.4);
        I_DCA_all[i_cut][i]->GetYaxis()->SetLabelSize(0.12);
        
        I_DCA_primary[i_cut][i]->GetXaxis()->SetTitleSize(0.16);
        I_DCA_primary[i_cut][i]->GetXaxis()->SetLabelSize(0.12);
        I_DCA_primary[i_cut][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_primary[i_cut][i]->GetYaxis()->SetTitleSize(0.16);
        I_DCA_primary[i_cut][i]->GetYaxis()->SetTitleOffset(0.4);
        I_DCA_primary[i_cut][i]->GetYaxis()->SetLabelSize(0.12);
        
        I_DCA_secondary[i_cut][i]->GetXaxis()->SetTitleSize(0.16);
        I_DCA_secondary[i_cut][i]->GetXaxis()->SetLabelSize(0.12);
        I_DCA_secondary[i_cut][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_secondary[i_cut][i]->GetYaxis()->SetTitleSize(0.16);
        I_DCA_secondary[i_cut][i]->GetYaxis()->SetTitleOffset(0.4);
        I_DCA_secondary[i_cut][i]->GetYaxis()->SetLabelSize(0.12);
        
        I_DCA_eff[i_cut][i] = new TH1F(Form("I_DCA_eff%i%i",i_cut,i),Form("Purity %s %s",s_cut[i_cut].Data(),s_proj[i].Data()),80,-10.,10.); I_DCA_eff[i_cut][i]->Sumw2();
        
        I_DCA_eff[i_cut][i]->GetXaxis()->SetTitleSize(0.16);
        I_DCA_eff[i_cut][i]->GetXaxis()->SetLabelSize(0.12);
        I_DCA_eff[i_cut][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_eff[i_cut][i]->GetYaxis()->SetTitleSize(0.16);
        I_DCA_eff[i_cut][i]->GetYaxis()->SetTitleOffset(0.4);
        I_DCA_eff[i_cut][i]->GetYaxis()->SetLabelSize(0.12);
        I_DCA_eff[i_cut][i]->GetYaxis()->SetTitle(Form("Purity"));
        
        I_DCA_cnt[i_cut][i] = new TH1F(Form("I_DCA_cnt%i%i",i_cut,i),Form("Contamination %s %s",s_cut[i_cut].Data(),s_proj[i].Data()),80,-10.,10.); I_DCA_cnt[i_cut][i]->Sumw2();
        
        I_DCA_cnt[i_cut][i]->GetXaxis()->SetTitleSize(0.16);
        I_DCA_cnt[i_cut][i]->GetXaxis()->SetLabelSize(0.12);
        I_DCA_cnt[i_cut][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_cnt[i_cut][i]->GetYaxis()->SetTitleSize(0.16);
        I_DCA_cnt[i_cut][i]->GetYaxis()->SetTitleOffset(0.4);
        I_DCA_cnt[i_cut][i]->GetYaxis()->SetLabelSize(0.12);
        I_DCA_cnt[i_cut][i]->GetYaxis()->SetTitle(Form("Secondary contamination"));
        
            for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                I_DCA_eta_all[i_cut][i][i_eta] = new TH1F(Form("I_DCA_eta_all%i%i%i",i_cut,i,i_eta),Form("All DCA %s %s at %1.1f #leq |#eta| < %1.1f",s_cut[i_cut].Data(),s_proj[i].Data(),eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.);
                I_DCA_eta_primary[i_cut][i][i_eta] = new TH1F(Form("I_DCA_eta_primary%i%i%i",i_cut,i,i_eta),Form("Primary DCA %s %s at %1.1f #leq |#eta| < %1.1f",s_cut[i_cut].Data(),s_proj[i].Data(),eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.);
                I_DCA_eta_secondary[i_cut][i][i_eta] = new TH1F(Form("I_DCA_eta_secondary%i%i%i",i_cut,i,i_eta),Form("Secondary DCA %s %s at %1.1f #leq |#eta| < %1.1f",s_cut[i_cut].Data(),s_proj[i].Data(),eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.);
                
                I_DCA_eta_all[i_cut][i][i_eta]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_eta_all[i_cut][i][i_eta]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_eta_all[i_cut][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_eta_all[i_cut][i][i_eta]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_eta_all[i_cut][i][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_eta_all[i_cut][i][i_eta]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_eta_primary[i_cut][i][i_eta]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_eta_primary[i_cut][i][i_eta]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_eta_primary[i_cut][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_eta_primary[i_cut][i][i_eta]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_eta_primary[i_cut][i][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_eta_primary[i_cut][i][i_eta]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_eta_secondary[i_cut][i][i_eta]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_eta_eff[i_cut][i][i_eta] = new TH1F(Form("I_DCA_eta_eff%i%i%i",i_cut,i,i_eta),Form("Purity %s %s for  %1.1f #leq |#eta| < %1.1f",s_cut[i_cut].Data(),s_proj[i].Data(),eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.); I_DCA_eta_eff[i_cut][i][i_eta]->Sumw2();
                I_DCA_eta_eff[i_cut][i][i_eta]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_eta_eff[i_cut][i][i_eta]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_eta_eff[i_cut][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_eta_eff[i_cut][i][i_eta]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_eta_eff[i_cut][i][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_eta_eff[i_cut][i][i_eta]->GetYaxis()->SetLabelSize(0.12);
                I_DCA_eta_eff[i_cut][i][i_eta]->GetYaxis()->SetTitle(Form("Purity"));
                
                I_DCA_eta_cnt[i_cut][i][i_eta] = new TH1F(Form("I_DCA_eta_cnt%i%i%i",i_cut,i,i_eta),Form("Contamination %s %s for  %1.1f #leq |#eta| < %1.1f",s_cut[i_cut].Data(),s_proj[i].Data(),eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.); I_DCA_eta_cnt[i_cut][i][i_eta]->Sumw2();
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetYaxis()->SetLabelSize(0.12);
                I_DCA_eta_cnt[i_cut][i][i_eta]->GetYaxis()->SetTitle(Form("Secondary contamination"));
                
            }

            for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
            
                I_DCA_pt_all[i_cut][i][i_pt] = new TH1F(Form("I_DCA_pt_all%i%i%i",i_cut,i,i_pt),Form("All DCA %s %s at %1.1f < p_{T} < %1.1f GeV/c",s_cut[i_cut].Data(),s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1]),80,-10.,10.);
                I_DCA_pt_primary[i_cut][i][i_pt] = new TH1F(Form("I_DCA_pt_primary%i%i%i",i_cut,i,i_pt),Form("Primary DCA %s %s at %1.1f < p_{T} < %1.1f GeV/c",s_cut[i_cut].Data(),s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1]),80,-10.,10.);
                I_DCA_pt_secondary[i_cut][i][i_pt] = new TH1F(Form("I_DCA_pt_secondary%i%i%i",i_cut,i,i_pt),Form("Secondary DCA %s %s at %1.1f < p_{T} < %1.1f GeV/c",s_cut[i_cut].Data(),s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1]),80,-10.,10.);
                
                I_DCA_pt_all[i_cut][i][i_pt]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_pt_all[i_cut][i][i_pt]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_pt_all[i_cut][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_pt_all[i_cut][i][i_pt]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_pt_all[i_cut][i][i_pt]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_pt_all[i_cut][i][i_pt]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_pt_primary[i_cut][i][i_pt]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_pt_primary[i_cut][i][i_pt]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_pt_primary[i_cut][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_pt_primary[i_cut][i][i_pt]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_pt_primary[i_cut][i][i_pt]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_pt_primary[i_cut][i][i_pt]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_pt_secondary[i_cut][i][i_pt]->GetYaxis()->SetLabelSize(0.12);
                
                I_DCA_pt_eff[i_cut][i][i_pt] = new TH1F(Form("I_DCA_pt_eff%i%i%i",i_cut,i,i_pt),Form("Purity %s %s for %1.1f < pT < %1.1f GeV/c",s_cut[i_cut].Data(),s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1]),80,-10.,10.); I_DCA_pt_eff[i_cut][i][i_pt]->Sumw2();
                
                I_DCA_pt_eff[i_cut][i][i_pt]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_pt_eff[i_cut][i][i_pt]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_pt_eff[i_cut][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_pt_eff[i_cut][i][i_pt]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_pt_eff[i_cut][i][i_pt]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_pt_eff[i_cut][i][i_pt]->GetYaxis()->SetLabelSize(0.12);
                I_DCA_pt_eff[i_cut][i][i_pt]->GetYaxis()->SetTitle(Form("Purity"));
                
                I_DCA_pt_cnt[i_cut][i][i_pt] = new TH1F(Form("I_DCA_pt_cnt%i%i%i",i_cut,i,i_pt),Form("Contamination %s %s for %1.1f < pT < %1.1f GeV/c",s_cut[i_cut].Data(),s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1]),80,-10.,10.); I_DCA_pt_cnt[i_cut][i][i_pt]->Sumw2();
                
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetXaxis()->SetTitleSize(0.16);
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetXaxis()->SetLabelSize(0.12);
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetYaxis()->SetTitleSize(0.16);
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetYaxis()->SetTitleOffset(0.4);
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetYaxis()->SetLabelSize(0.12);
                I_DCA_pt_cnt[i_cut][i][i_pt]->GetYaxis()->SetTitle(Form("Purity"));
   
                for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){

                    h_dca_all[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta));
                    h_dca_all[i_cut][i][i_pt][i_eta]->Rebin(5);
                    f_dca_all[i_cut][i][i_pt][i_eta] = (TF1*) cutfile->Get(Form("f_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta));
                    //h_dca_all[i_cut][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                    //h_dca_all[i_cut][i][i_pt][i_eta] = new TH1F(Form("h_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta),Form("h_dca_all %i %s for %1.1f < pT < %1.1f, %1.1f < |#eta| < %1.1f",i_cut,s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1],eta_bins[i_eta],eta_bins[i_eta+1]),400,-10.,10.);

                    h_dca_primary[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    h_dca_primary[i_cut][i][i_pt][i_eta]->Rebin(5);
                    f_dca_primary[i_cut][i][i_pt][i_eta] = (TF1*) cutfile->Get(Form("f_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    //h_dca_primary[i_cut][i][i_pt][i_eta]->GetFunction(Form("f_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                    //h_dca_primary[i_cut][i][i_pt][i_eta] = new TH1F(Form("h_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta),Form("h_dca_primary %i %s for %1.1f < pT < %1.1f, %1.1f < |#eta| < %1.1f",i_cut,s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1],eta_bins[i_eta],eta_bins[i_eta+1]),400,-10.,10.);

                    h_dca_secondary[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    h_dca_secondary[i_cut][i][i_pt][i_eta]->Rebin(5);
                    f_dca_secondary[i_cut][i][i_pt][i_eta] = (TF1*) cutfile->Get(Form("f_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    //h_dca_secondary[i_cut][i][i_pt][i_eta]->GetFunction(Form("f_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                    //h_dca_secondary[i_cut][i][i_pt][i_eta] = new TH1F(Form("h_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta),Form("h_dca_secondary %i %s for %1.1f < pT < %1.1f, %1.1f < |#eta| < %1.1f",i_cut,s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1],eta_bins[i_eta],eta_bins[i_eta+1]),400,-10.,10.);
                    
                    h_dca_eff[i_cut][i][i_pt][i_eta] = new TH1F(Form("h_dca_eff%i%i%i%i",i_cut,i,i_pt,i_eta),Form("h_dca_eff %i %s for %1.1f < pT < %1.1f, %1.1f #leq |#eta| < %1.1f",i_cut,s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1],eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.); h_dca_eff[i_cut][i][i_pt][i_eta]->Sumw2();
                    
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.16);
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.12);
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitle("DCA");
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.16);
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.12);
                    h_dca_eff[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitle(Form("Purity"));
                    
                    h_dca_cnt[i_cut][i][i_pt][i_eta] = new TH1F(Form("h_dca_cnt%i%i%i%i",i_cut,i,i_pt,i_eta),Form("h_dca_cnt %i %s for %1.1f < pT < %1.1f, %1.1f #leq |#eta| < %1.1f",i_cut,s_proj[i].Data(),pt_bins[i_pt],pt_bins[i_pt+1],eta_bins[i_eta],eta_bins[i_eta+1]),80,-10.,10.); h_dca_cnt[i_cut][i][i_pt][i_eta]->Sumw2();
                    
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.16);
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.12);
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitle("DCA");
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.16);
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.4);
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.12);
                    h_dca_cnt[i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitle(Form("Secondary contamination"));
                    
                    for (Int_t k=0;k<3;k++){
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta] = (TH2F*) file->Get(Form("h_DCA_chi2_NDF%i%i%i%i%i",k,i_cut,i,i_pt,i_eta));
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta] = (TH2F*) file->Get(Form("h_DCA_chi2_vertex%i%i%i%i%i",k,i_cut,i,i_pt,i_eta));
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitle(Form("#chi^{2}/NDF"));
                        h_DCA_chi2_NDF[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitle(Form("%s DCA %s",s_DCA[k].Data(),s_proj[i].Data()));
                        
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetXaxis()->SetTitle(Form("#chi^{2}_{vertex}"));
                        h_DCA_chi2_vertex[k][i_cut][i][i_pt][i_eta]->GetYaxis()->SetTitle(Form("%s DCA %s",s_DCA[k].Data(),s_proj[i].Data()));
                    }
                    
                }
            }
        }
    }
    
    for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
        for (Int_t i=0;i<n_proj;i++){
            for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
                for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                    I_DCA_all[i_cut][i]->Add(h_dca_all[i_cut][i][i_pt][i_eta]);
                    I_DCA_primary[i_cut][i]->Add(h_dca_primary[i_cut][i][i_pt][i_eta]);
                    I_DCA_secondary[i_cut][i]->Add(h_dca_secondary[i_cut][i][i_pt][i_eta]);
                    
                    I_DCA_pt_all[i_cut][i][i_pt]->Add(h_dca_all[i_cut][i][i_pt][i_eta]);
                    I_DCA_pt_primary[i_cut][i][i_pt]->Add(h_dca_primary[i_cut][i][i_pt][i_eta]);
                    I_DCA_pt_secondary[i_cut][i][i_pt]->Add(h_dca_secondary[i_cut][i][i_pt][i_eta]);
                    
                    I_DCA_eta_all[i_cut][i][i_eta]->Add(h_dca_all[i_cut][i][i_pt][i_eta]);
                    I_DCA_eta_primary[i_cut][i][i_eta]->Add(h_dca_primary[i_cut][i][i_pt][i_eta]);
                    I_DCA_eta_secondary[i_cut][i][i_eta]->Add(h_dca_secondary[i_cut][i][i_pt][i_eta]);
                }
            }
        }
    }
    
    for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
        for (Int_t i=0;i<n_proj;i++){
        
            I_DCA_eff[i_cut][i]->Divide(I_DCA_primary[i_cut][i],I_DCA_all[i_cut][i]);
            
            for (Int_t i_bin=0;i_bin<80;i_bin++){
                I_DCA_cnt[i_cut][i]->SetBinContent(i_bin,1-I_DCA_eff[i_cut][i]->GetBinContent(i_bin));
                I_DCA_cnt[i_cut][i]->SetBinError(i_bin,I_DCA_eff[i_cut][i]->GetBinError(i_bin));
            }
        
            for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
                I_DCA_pt_eff[i_cut][i][i_pt]->Divide(I_DCA_pt_primary[i_cut][i][i_pt],I_DCA_pt_all[i_cut][i][i_pt]);
                
                for (Int_t i_bin=0;i_bin<80;i_bin++){
                    I_DCA_pt_cnt[i_cut][i][i_pt]->SetBinContent(i_bin,1-I_DCA_pt_eff[i_cut][i][i_pt]->GetBinContent(i_bin));
                    I_DCA_pt_cnt[i_cut][i][i_pt]->SetBinError(i_bin,I_DCA_pt_eff[i_cut][i][i_pt]->GetBinError(i_bin));
                }
            }
            for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                I_DCA_eta_eff[i_cut][i][i_eta]->Divide(I_DCA_eta_primary[i_cut][i][i_eta],I_DCA_eta_all[i_cut][i][i_eta]);
                
                for (Int_t i_bin=0;i_bin<80;i_bin++){
                    I_DCA_eta_cnt[i_cut][i][i_eta]->SetBinContent(i_bin,1-I_DCA_eta_eff[i_cut][i][i_eta]->GetBinContent(i_bin));
                    I_DCA_eta_cnt[i_cut][i][i_eta]->SetBinError(i_bin,I_DCA_eta_eff[i_cut][i][i_eta]->GetBinError(i_bin));
                }
                
            }
        }
    }
            
    
    for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
        for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
            for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                h_chi2_vertex[i_cut][i_pt][i_eta] = (TH1F*) file->Get(Form("h_chi2_vertex%i%i%i",i_cut,i_pt,i_eta));
                h_chi2_NDF[i_cut][i_pt][i_eta] = (TH1F*) file->Get(Form("h_chi2_NDF%i%i%i",i_cut,i_pt,i_eta));
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta] = (TH2F*) file->Get(Form("h_chi2_NDF_vertex%i%i%i",i_cut,i_pt,i_eta));
                
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_chi2_NDF[i_cut][i_pt][i_eta]->GetXaxis()->SetTitle(Form("#chi^{2}/NDF"));
                
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_chi2_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetTitle(Form("#chi^{2}_{vertex}"));
                
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetXaxis()->SetTitle(Form("#chi^{2}/NDF"));
                h_chi2_NDF_vertex[i_cut][i_pt][i_eta]->GetYaxis()->SetTitle(Form("#chi^{2}_{vertex}"));
            }
        }
    }
                    
    
    TCanvas* canv[8][n_proj][n_pt_bin][n_eta_bin];
    TLine*   line = new TLine();
    TLine*   line1 = new TLine();
    TLine*   cutline1 = new TLine();
    TLine*   cutline2 = new TLine();
    line->SetLineWidth(3.);
    line->SetLineStyle(2);
    line1->SetLineStyle(3);
    cutline1->SetLineWidth(3.);
    cutline2->SetLineWidth(3.);
    
    TLegend* leg1;
    TLegend* leg2;
    TLegend* leg3;
    TLegend* leg4;
    TLegend* leg5;
    TLegend* leg6;
    TLegend* leg7;
    TLegend* leg8;
    TLegend* leg9;
    TLegend* leg10;
    for (Int_t i=0;i<n_proj;i++){
        for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
            for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                    
                canv[0][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",0,i,i_pt,i_eta),Form("canv%i%i%i%i",0,i,i_pt,i_eta),700,500);
                canv[0][i][i_pt][i_eta]->SetLogy();
                canv[0][i][i_pt][i_eta]->cd();
                
                canv[0][i][i_pt][i_eta]->SetBottomMargin(0.17);
                canv[0][i][i_pt][i_eta]->SetLeftMargin(0.13);
                
                leg1 = new TLegend(0.15,0.69,0.5,0.87);
                leg1->SetBorderSize(0);
                //leg2 = new TLegend(0.5,0.69,0.88,0.87);
                //leg2->SetBorderSize(0);
                
                h_dca_all[0][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_dca_all[0][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_dca_all[0][i][i_pt][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                h_dca_all[0][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_dca_all[0][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_dca_all[0][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                
                h_dca_all[0][i][i_pt][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
                h_dca_all[0][i][i_pt][i_eta]->GetYaxis()->SetRangeUser(1.,1e11);
                
                h_dca_all[0][i][i_pt][i_eta]->SetMarkerStyle(marker_style[0]);
                h_dca_all[0][i][i_pt][i_eta]->SetMarkerColor(marker_color[0]);
                h_dca_all[0][i][i_pt][i_eta]->SetLineColor(marker_color[0]);
                //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_all[0][i][i_pt][i_eta]->SetLineWidth(2);
                
                h_dca_primary[0][i][i_pt][i_eta]->SetMarkerStyle(marker_style[2]);
                h_dca_primary[0][i][i_pt][i_eta]->SetMarkerColor(marker_color[1]);
                h_dca_primary[0][i][i_pt][i_eta]->SetLineColor(marker_color[1]);
                //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_primary[0][i][i_pt][i_eta]->SetLineWidth(2);
                
                h_dca_secondary[0][i][i_pt][i_eta]->SetMarkerStyle(marker_style[2]);
                h_dca_secondary[0][i][i_pt][i_eta]->SetMarkerColor(marker_color[2]);
                h_dca_secondary[0][i][i_pt][i_eta]->SetLineColor(marker_color[2]);
                //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_secondary[0][i][i_pt][i_eta]->SetLineWidth(2);
                
                leg1->AddEntry(h_dca_all[0][i][i_pt][i_eta],"all","p");
                leg1->AddEntry(h_dca_primary[0][i][i_pt][i_eta],"primary","p");
                leg1->AddEntry(h_dca_secondary[0][i][i_pt][i_eta],"secondary","p");
                
                //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
                //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
                
                //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                
                h_dca_all[0][i][i_pt][i_eta]->Draw("P,E,X0,HIST");
                //h_dca_all[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                h_dca_primary[0][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                //h_dca_primary[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                h_dca_secondary[0][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                leg1->Draw();
                //leg2->Draw();
                //h_dca_secondary[0][i][i_pt][i_eta]->Draw("P,E,X0,SAME");
                //h_dca_secondary[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME");
                
                canv[0][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/dca_%i_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                canv[7][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",7,i,i_pt,i_eta),Form("canv%i%i%i%i",7,i,i_pt,i_eta),700,500);
                canv[7][i][i_pt][i_eta]->SetLogy();
                canv[7][i][i_pt][i_eta]->cd();
                
                canv[7][i][i_pt][i_eta]->SetBottomMargin(0.17);
                canv[7][i][i_pt][i_eta]->SetLeftMargin(0.13);
                
                //leg1 = new TLegend(0.15,0.69,0.5,0.87);
                //leg1->SetBorderSize(0);
                leg2 = new TLegend(0.15,0.69,0.5,0.87);
                leg2->SetBorderSize(0);
                
                h_dca_all[1][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_dca_all[1][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_dca_all[1][i][i_pt][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                h_dca_all[1][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_dca_all[1][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_dca_all[1][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                
                h_dca_all[1][i][i_pt][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
                h_dca_all[1][i][i_pt][i_eta]->GetYaxis()->SetRangeUser(1.,1e11);
                
                h_dca_all[1][i][i_pt][i_eta]->SetMarkerStyle(marker_style[1]);
                h_dca_all[1][i][i_pt][i_eta]->SetMarkerColor(marker_color[0]);
                h_dca_all[1][i][i_pt][i_eta]->SetLineColor(marker_color[0]);
                //h_dca_all[1][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_all[1][i][i_pt][i_eta]->SetLineWidth(2);
                
                h_dca_primary[1][i][i_pt][i_eta]->SetMarkerStyle(marker_style[3]);
                h_dca_primary[1][i][i_pt][i_eta]->SetMarkerColor(marker_color[1]);
                h_dca_primary[1][i][i_pt][i_eta]->SetLineColor(marker_color[1]);
                //h_dca_all[1][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_primary[1][i][i_pt][i_eta]->SetLineWidth(2);
                
                h_dca_secondary[1][i][i_pt][i_eta]->SetMarkerStyle(marker_style[3]);
                h_dca_secondary[1][i][i_pt][i_eta]->SetMarkerColor(marker_color[2]);
                h_dca_secondary[1][i][i_pt][i_eta]->SetLineColor(marker_color[2]);
                //h_dca_all[1][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_secondary[1][i][i_pt][i_eta]->SetLineWidth(2);
                
                leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"all","p");
                leg2->AddEntry(h_dca_primary[1][i][i_pt][i_eta],"primary","p");
                leg2->AddEntry(h_dca_secondary[1][i][i_pt][i_eta],"secondary","p");
                
                //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
                //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
                
                //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
                
                //h_dca_all[0][i][i_pt][i_eta]->Draw("P,E,X0,HIST");
                h_dca_all[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                //h_dca_primary[0][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                h_dca_primary[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                h_dca_secondary[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME,HIST");
                //leg1->Draw();
                leg2->Draw();
                //h_dca_secondary[0][i][i_pt][i_eta]->Draw("P,E,X0,SAME");
                //h_dca_secondary[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME");
                
                canv[7][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/dca_cut_%i_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                canv[1][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",1,i,i_pt,i_eta),Form("canv%i%i%i%i",1,i,i_pt,i_eta),700,500);
                canv[1][i][i_pt][i_eta]->cd();
                canv[1][i][i_pt][i_eta]->SetBottomMargin(0.17);
                canv[1][i][i_pt][i_eta]->SetLeftMargin(0.13);
                
                leg3 = new TLegend(0.15,0.69,0.5,0.87);
                leg3->SetBorderSize(0);
                
                h_dca_eff[0][i][i_pt][i_eta]->Divide(h_dca_primary[0][i][i_pt][i_eta],h_dca_all[0][i][i_pt][i_eta]);
                
                h_dca_eff[1][i][i_pt][i_eta]->Divide(h_dca_primary[1][i][i_pt][i_eta],h_dca_all[1][i][i_pt][i_eta]);
                
                for (Int_t i_bin=0;i_bin<80;i_bin++){
                    h_dca_cnt[0][i][i_pt][i_eta]->SetBinContent(i_bin,1-h_dca_eff[0][i][i_pt][i_eta]->GetBinContent(i_bin));
                    h_dca_cnt[0][i][i_pt][i_eta]->SetBinError(i_bin,h_dca_eff[0][i][i_pt][i_eta]->GetBinError(i_bin));
                    h_dca_cnt[1][i][i_pt][i_eta]->SetBinContent(i_bin,1-h_dca_eff[1][i][i_pt][i_eta]->GetBinContent(i_bin));
                    h_dca_cnt[1][i][i_pt][i_eta]->SetBinError(i_bin,h_dca_eff[1][i][i_pt][i_eta]->GetBinError(i_bin));
                }
                
                h_dca_cnt[0][i][i_pt][i_eta]->GetXaxis()->SetTitleSize(0.08);
                h_dca_cnt[0][i][i_pt][i_eta]->GetXaxis()->SetLabelSize(0.06);
                h_dca_cnt[0][i][i_pt][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
                h_dca_cnt[0][i][i_pt][i_eta]->GetYaxis()->SetTitleSize(0.08);
                h_dca_cnt[0][i][i_pt][i_eta]->GetYaxis()->SetTitleOffset(0.8);
                h_dca_cnt[0][i][i_pt][i_eta]->GetYaxis()->SetLabelSize(0.06);
                
                h_dca_cnt[0][i][i_pt][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
                h_dca_cnt[0][i][i_pt][i_eta]->GetYaxis()->SetRangeUser(0.,0.5);
                
                h_dca_cnt[0][i][i_pt][i_eta]->SetMarkerStyle(marker_style[0]);
                h_dca_cnt[0][i][i_pt][i_eta]->SetMarkerColor(marker_color[1]);
                h_dca_cnt[0][i][i_pt][i_eta]->SetLineColor(marker_color[1]);
                //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_cnt[0][i][i_pt][i_eta]->SetLineWidth(2);
                
                h_dca_cnt[1][i][i_pt][i_eta]->SetMarkerStyle(marker_style[1]);
                h_dca_cnt[1][i][i_pt][i_eta]->SetMarkerColor(marker_color[2]);
                h_dca_cnt[1][i][i_pt][i_eta]->SetLineColor(marker_color[2]);
                //h_dca_all[1][i][i_pt][i_eta]->SetMarkerSize(2.);
                h_dca_cnt[1][i][i_pt][i_eta]->SetLineWidth(2);
                
                leg3->AddEntry(h_dca_cnt[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
                leg3->AddEntry(h_dca_cnt[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
                
                h_dca_cnt[0][i][i_pt][i_eta]->Draw("P,E,X0");
                h_dca_cnt[1][i][i_pt][i_eta]->Draw("P,E,X0,SAME");
                line->DrawLine(-3.,1.,3.,1.);
                line1->DrawLine(-3.,0.1,3.,0.1);
                leg3->Draw();
                Float_t sigma = 2*f_dca_all[1][i][i_pt][i_eta]->GetParameter(2);
                //Int_t bin_1 = h_dca_eff[1][i][i_pt][i_eta]->FindBin(0-sigma);
                //Int_t bin_2 = h_dca_eff[1][i][i_pt][i_eta]->FindBin(0+sigma);
                cutline1->DrawLine(-sigma,0.,-sigma,0.5);
                cutline1->DrawLine(+sigma,0.,+sigma,0.5);
                
                
                canv[1][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/ratio_dca_%i_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                canv[2][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",2,i,i_pt,i_eta),Form("CHI_SQWR%i%i%i%i",2,i,i_pt,i_eta),700,500);
                canv[2][i][i_pt][i_eta]->SetLogy();
                canv[2][i][i_pt][i_eta]->cd();
                
                canv[2][i][i_pt][i_eta]->SetBottomMargin(0.19);
                canv[2][i][i_pt][i_eta]->SetLeftMargin(0.13);
                
                leg4 = new TLegend(0.65,0.69,0.87,0.88);
                leg4->SetBorderSize(0);
                leg5 = new TLegend(0.65,0.69,0.87,0.88);
                leg5->SetBorderSize(0);
                
                h_chi2_NDF[0][i_pt][i_eta]->SetMarkerStyle(marker_style[0]);
                h_chi2_NDF[0][i_pt][i_eta]->SetMarkerColor(marker_color[0]);
                h_chi2_NDF[0][i_pt][i_eta]->SetLineColor(marker_color[0]);
                h_chi2_NDF[0][i_pt][i_eta]->SetLineWidth(2);
                
                h_chi2_NDF[1][i_pt][i_eta]->SetMarkerStyle(marker_style[2]);
                h_chi2_NDF[1][i_pt][i_eta]->SetMarkerColor(marker_color[2]);
                h_chi2_NDF[1][i_pt][i_eta]->SetLineColor(marker_color[2]);
                h_chi2_NDF[1][i_pt][i_eta]->SetLineWidth(2);
                
                if (i==0){
                    h_chi2_NDF[0][i_pt][i_eta]->Draw("");
                    h_chi2_NDF[1][i_pt][i_eta]->Draw("SAME");
                    leg4->AddEntry(h_chi2_NDF[0][i_pt][i_eta],"no #chi^{2} cut","l");
                    leg4->AddEntry(h_chi2_NDF[1][i_pt][i_eta],"with #chi^{2} cut","l");
                    leg4->Draw();
                }
                
                h_chi2_vertex[0][i_pt][i_eta]->SetMarkerStyle(marker_style[0]);
                h_chi2_vertex[0][i_pt][i_eta]->SetMarkerColor(marker_color[0]);
                h_chi2_vertex[0][i_pt][i_eta]->SetLineColor(marker_color[0]);
                h_chi2_vertex[0][i_pt][i_eta]->SetLineWidth(2);
                
                h_chi2_vertex[1][i_pt][i_eta]->SetMarkerStyle(marker_style[2]);
                h_chi2_vertex[1][i_pt][i_eta]->SetMarkerColor(marker_color[2]);
                h_chi2_vertex[1][i_pt][i_eta]->SetLineColor(marker_color[2]);
                h_chi2_vertex[1][i_pt][i_eta]->SetLineWidth(2);
                
                if (i==1){
                    h_chi2_vertex[0][i_pt][i_eta]->Draw("");
                    h_chi2_vertex[1][i_pt][i_eta]->Draw("SAME");
                    leg5->AddEntry(h_chi2_vertex[0][i_pt][i_eta],"no #chi^{2} cut","l");
                    leg5->AddEntry(h_chi2_vertex[1][i_pt][i_eta],"with #chi^{2} cut","l");
                    leg5->Draw();
                }
                
                if (i==0) canv[2][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Chi2/chi2_NDF_%i_%i.png",i_pt,i_eta),"recreate");
                if (i==1) canv[2][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Chi2/chi2_vertex_%i_%i.png",i_pt,i_eta),"recreate");
                
                canv[3][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",3,i,i_pt,i_eta),Form("CHI_SQWR%i%i%i%i",3,i,i_pt,i_eta),700,500);
                canv[3][i][i_pt][i_eta]->SetLogz();
                canv[3][i][i_pt][i_eta]->cd();
                canv[3][i][i_pt][i_eta]->SetBottomMargin(0.19);
                canv[3][i][i_pt][i_eta]->SetLeftMargin(0.13);
                if (i==0) {
                    h_chi2_NDF_vertex[0][i_pt][i_eta]->Draw("COLZ");
                    canv[3][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Correlations/chi2_NDF_vertex_%i_%i.png",i_pt,i_eta),"recreate");
                }
                    
                canv[4][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",4,i,i_pt,i_eta),Form("CHI_SQWR%i%i%i%i",4,i,i_pt,i_eta),700,500);
                canv[4][i][i_pt][i_eta]->SetLogz();
                canv[4][i][i_pt][i_eta]->cd();
                canv[4][i][i_pt][i_eta]->SetBottomMargin(0.19);
                canv[4][i][i_pt][i_eta]->SetLeftMargin(0.13);
                h_DCA_chi2_vertex[0][0][i][i_pt][i_eta]->Draw("COLZ");

                canv[4][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Correlations/DCA_%i_chi2_vertex_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                canv[5][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",5,i,i_pt,i_eta),Form("CHI_SQWR%i%i%i%i",5,i,i_pt,i_eta),700,500);
                canv[5][i][i_pt][i_eta]->SetLogz();
                canv[5][i][i_pt][i_eta]->cd();
                canv[5][i][i_pt][i_eta]->SetBottomMargin(0.19);
                canv[5][i][i_pt][i_eta]->SetLeftMargin(0.13);
                h_DCA_chi2_NDF[0][0][i][i_pt][i_eta]->Draw("COLZ");

                canv[5][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Correlations/DCA_%i_chi2_NDF_no_cut_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                canv[6][i][i_pt][i_eta] = new TCanvas(Form("canv%i%i%i%i",6,i,i_pt,i_eta),Form("CHI_SQWR%i%i%i%i",6,i,i_pt,i_eta),700,500);
                canv[6][i][i_pt][i_eta]->SetLogz();
                canv[6][i][i_pt][i_eta]->cd();
                canv[6][i][i_pt][i_eta]->SetBottomMargin(0.19);
                canv[6][i][i_pt][i_eta]->SetLeftMargin(0.13);
                h_DCA_chi2_NDF[0][1][i][i_pt][i_eta]->Draw("COLZ");

                canv[6][i][i_pt][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Correlations/DCA_%i_chi2_NDF_w_cut_%i_%i.png",i,i_pt,i_eta),"recreate");
                
                
            }
        }
    }
    
    TCanvas* kincanv[14];
    kincanv[0] = new TCanvas(Form("kincanv%i",0),Form("KINEM%i",0),700,500);
    kincanv[0]->SetLogy();
    kincanv[0]->cd();
    kincanv[0]->SetBottomMargin(0.19);
    kincanv[0]->SetLeftMargin(0.13);
    
    leg6 = new TLegend(0.65,0.69,0.87,0.88);
    leg6->SetBorderSize(0);
    
    pt_total[0]->SetMarkerStyle(marker_style[0]);
    pt_total[0]->SetMarkerColor(marker_color[0]);
    pt_total[0]->SetLineColor(marker_color[0]);
    pt_total[0]->SetLineWidth(2);
    pt_total[0]->GetYaxis()->SetRangeUser(1.,1e8);
    
    pt_total[1]->SetMarkerStyle(marker_style[2]);
    pt_total[1]->SetMarkerColor(marker_color[2]);
    pt_total[1]->SetLineColor(marker_color[2]);
    pt_total[1]->SetLineWidth(2);
    
    leg6->AddEntry(pt_total[0],"no track cut","l");
    leg6->AddEntry(pt_total[1],"with track cut","l");
    
    pt_total[0]->Draw("");
    pt_total[1]->Draw("SAME");
    
    leg6->Draw();
    
    kincanv[0]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/pt_spectre.png"),"recreate");
    
    kincanv[1] = new TCanvas(Form("kincanv%i",1),Form("KINEM%i",1),700,500);
    kincanv[1]->SetLogy();
    kincanv[1]->cd();
    kincanv[1]->SetBottomMargin(0.19);
    kincanv[1]->SetLeftMargin(0.13);
    
    leg7 = new TLegend(0.65,0.69,0.87,0.88);
    leg7->SetBorderSize(0);
    
    eta_total[0]->SetMarkerStyle(marker_style[0]);
    eta_total[0]->SetMarkerColor(marker_color[0]);
    eta_total[0]->SetLineColor(marker_color[0]);
    eta_total[0]->SetLineWidth(2);
    eta_total[0]->GetYaxis()->SetRangeUser(1.,1e8);
    
    eta_total[1]->SetMarkerStyle(marker_style[2]);
    eta_total[1]->SetMarkerColor(marker_color[2]);
    eta_total[1]->SetLineColor(marker_color[2]);
    eta_total[1]->SetLineWidth(2);
    
    eta_total[0]->Draw("");
    eta_total[1]->Draw("SAME");
    
    leg7->AddEntry(eta_total[0],"no track cut","l");
    leg7->AddEntry(eta_total[1],"with track cut","l");
    
    leg7->Draw();
    
    kincanv[1]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/eta_spectre.png"),"recreate");
    
    kincanv[2] = new TCanvas(Form("kincanv%i",2),Form("KINEM%i",2),700,500);
    kincanv[2]->SetLogz();
    kincanv[2]->cd();
    kincanv[2]->SetBottomMargin(0.19);
    kincanv[2]->SetLeftMargin(0.13);
    
    pt_vs_n_hits_total[0]->Draw("COLZ");
    
    kincanv[2]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/pt_n_hits_before_cut.png"),"recreate");
    
    kincanv[3] = new TCanvas(Form("kincanv%i",3),Form("KINEM%i",3),700,500);
    kincanv[3]->SetLogz();
    kincanv[3]->cd();
    kincanv[3]->SetBottomMargin(0.19);
    kincanv[3]->SetLeftMargin(0.13);
    
    pt_vs_n_hits_total[1]->Draw("COLZ");
    
    kincanv[3]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/pt_n_hits_after_cut.png"),"recreate");
    
    kincanv[4] = new TCanvas(Form("kincanv%i",4),Form("KINEM%i",4),700,500);
    kincanv[4]->SetLogz();
    kincanv[4]->cd();
    kincanv[4]->SetBottomMargin(0.19);
    kincanv[4]->SetLeftMargin(0.13);
    
    eta_vs_n_hits_total[0]->Draw("COLZ");
    
    kincanv[4]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/eta_n_hits_before_cut.png"),"recreate");
    
    kincanv[5] = new TCanvas(Form("kincanv%i",5),Form("KINEM%i",5),700,500);
    kincanv[5]->SetLogz();
    kincanv[5]->cd();
    kincanv[5]->SetBottomMargin(0.19);
    kincanv[5]->SetLeftMargin(0.13);
    
    eta_vs_n_hits_total[1]->Draw("COLZ");
    
    kincanv[5]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/eta_n_hits_after_cut.png"),"recreate");
    
    kincanv[6] = new TCanvas(Form("kincanv%i",6),Form("KINEM%i",6),700,500);
    kincanv[6]->SetLogz();
    kincanv[6]->cd();
    kincanv[6]->SetBottomMargin(0.19);
    kincanv[6]->SetLeftMargin(0.13);
    
    pt_vs_eta_total[0]->Draw("COLZ");
    
    kincanv[6]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/pt_vs_eta_before_cut.png"),"recreate");
    
    kincanv[7] = new TCanvas(Form("kincanv%i",7),Form("KINEM%i",7),700,500);
    kincanv[7]->SetLogz();
    kincanv[7]->cd();
    kincanv[7]->SetBottomMargin(0.19);
    kincanv[7]->SetLeftMargin(0.13);
    
    pt_vs_eta_total[1]->Draw("COLZ");
    
    kincanv[7]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/pt_vs_eta_after_cut.png"),"recreate");
    
    kincanv[8] = new TCanvas(Form("kincanv%i",8),Form("KINEM%i",8),700,500);
    kincanv[8]->SetLogz();
    kincanv[8]->cd();
    kincanv[8]->SetBottomMargin(0.19);
    kincanv[8]->SetLeftMargin(0.13);
    
    mc_pt_vs_n_hits_total[0]->Draw("COLZ");
    
    kincanv[8]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_pt_n_hits_before_cut.png"),"recreate");
    
    kincanv[9] = new TCanvas(Form("kincanv%i",9),Form("KINEM%i",9),700,500);
    kincanv[9]->SetLogz();
    kincanv[9]->cd();
    kincanv[9]->SetBottomMargin(0.19);
    kincanv[9]->SetLeftMargin(0.13);
    
    mc_pt_vs_n_hits_total[1]->Draw("COLZ");
    
    kincanv[9]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_pt_n_hits_after_cut.png"),"recreate");
    
    kincanv[10] = new TCanvas(Form("kincanv%i",10),Form("KINEM%i",10),700,500);
    kincanv[10]->SetLogz();
    kincanv[10]->cd();
    kincanv[10]->SetBottomMargin(0.19);
    kincanv[10]->SetLeftMargin(0.13);
    
    mc_eta_vs_n_hits_total[0]->Draw("COLZ");
    
    kincanv[10]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_eta_n_hits_before_cut.png"),"recreate");
    
    kincanv[11] = new TCanvas(Form("kincanv%i",11),Form("KINEM%i",11),700,500);
    kincanv[11]->SetLogz();
    kincanv[11]->cd();
    kincanv[11]->SetBottomMargin(0.19);
    kincanv[11]->SetLeftMargin(0.13);
    
    mc_eta_vs_n_hits_total[1]->Draw("COLZ");
    
    kincanv[11]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_eta_n_hits_after_cut.png"),"recreate");
    
    kincanv[12] = new TCanvas(Form("kincanv%i",12),Form("KINEM%i",12),700,500);
    kincanv[12]->SetLogz();
    kincanv[12]->cd();
    kincanv[12]->SetBottomMargin(0.19);
    kincanv[12]->SetLeftMargin(0.13);
    
    mc_pt_vs_eta_total[0]->Draw("COLZ");
    
    kincanv[12]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_pt_vs_eta_before_cut.png"),"recreate");
    
    kincanv[13] = new TCanvas(Form("kincanv%i",13),Form("KINEM%i",13),700,500);
    kincanv[13]->SetLogz();
    kincanv[13]->cd();
    kincanv[13]->SetBottomMargin(0.19);
    kincanv[13]->SetLeftMargin(0.13);
    
    mc_pt_vs_eta_total[1]->Draw("COLZ");
    
    kincanv[13]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/Kinematics/mc_pt_vs_eta_after_cut.png"),"recreate");
    
    TCanvas* canvas = new TCanvas(Form("canvas"),Form("canvas"),900,400);
    canvas->Divide(2,1);
    canvas->cd(1);
    canvas->cd(1)->SetLogy();
    leg9 = new TLegend(0.15,0.69,0.5,0.87);
    leg9->SetBorderSize(0);
    h_dca_all[0][0][1][0]->GetFunction("f_dca_all0010")->SetBit(TF1::kNotDraw);
    h_dca_primary[0][0][1][0]->GetFunction("f_dca_primary0010")->SetBit(TF1::kNotDraw);
    h_dca_secondary[0][0][1][0]->GetFunction("f_dca_secondary0010")->SetBit(TF1::kNotDraw);
    h_dca_all[0][0][1][0]->Draw("P,E,X0");
    h_dca_primary[0][0][1][0]->Draw("P,E,X0,SAME");
    h_dca_secondary[0][0][1][0]->Draw("P,E,X0,SAME");
    leg9->AddEntry(h_dca_all[0][i][i_pt][i_eta],"all","p");
    leg9->AddEntry(h_dca_primary[0][i][i_pt][i_eta],"primary","p");
    leg9->AddEntry(h_dca_secondary[0][i][i_pt][i_eta],"secondary","p");
    leg9->Draw();
    
    canvas->cd(2);
    canvas->cd(2)->SetLogy();
    leg10 = new TLegend(0.15,0.69,0.5,0.87);
    leg10->SetBorderSize(0);
    h_dca_all[0][0][1][0]->GetYaxis()->SetRangeUser(0.5*1e2,1e11);
    h_dca_all[1][0][1][0]->GetYaxis()->SetRangeUser(0.5*1e2,1e11);
    h_dca_all[1][0][1][0]->GetXaxis()->SetRangeUser(-3.,3.);
    h_dca_all[1][0][1][0]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[0].Data()));
    h_dca_all[1][0][1][0]->GetXaxis()->SetTitleSize(0.08);
    h_dca_all[1][0][1][0]->GetXaxis()->SetLabelSize(0.06);
    h_dca_all[1][0][1][0]->GetYaxis()->SetLabelSize(0.06);
    h_dca_all[1][0][1][0]->GetFunction("f_dca_all1010")->SetBit(TF1::kNotDraw);
    h_dca_primary[1][0][1][0]->GetFunction("f_dca_primary1010")->SetBit(TF1::kNotDraw);
    h_dca_secondary[1][0][1][0]->GetFunction("f_dca_secondary1010")->SetBit(TF1::kNotDraw);
    h_dca_all[1][0][1][0]->Draw("P,E,X0");
    h_dca_primary[1][0][1][0]->Draw("P,E,X0,SAME");
    h_dca_secondary[1][0][1][0]->Draw("P,E,X0,SAME");
    leg10->AddEntry(h_dca_all[0][i][i_pt][i_eta],"all","p");
    leg10->AddEntry(h_dca_primary[0][i][i_pt][i_eta],"primary","p");
    leg10->AddEntry(h_dca_secondary[0][i][i_pt][i_eta],"secondary","p");
    leg10->Draw();
    
    canvas->cd(1)->SetBottomMargin(0.17);
    canvas->cd(1)->SetLeftMargin(0.13);
    canvas->cd(2)->SetBottomMargin(0.17);
    canvas->cd(2)->SetLeftMargin(0.13);
    
    canvas->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/DCA_check.png"),"recreate");
    
    TCanvas* canvas1 = new TCanvas(Form("canvas1"),Form("canvas1"),700,500);
    canvas1->cd();
    canvas1->SetLogy();
    leg8 = new TLegend(0.15,0.69,0.57,0.88);
    leg8->SetBorderSize(0);
    
    h_hits_mpd[0]->SetMarkerStyle(marker_style[1]);
    h_hits_mpd[0]->SetMarkerColor(marker_color[1]);
    h_hits_mpd[0]->SetLineColor(marker_color[1]);
    h_hits_mpd[0]->SetLineWidth(2);
    
    h_hits_mpd[1]->SetMarkerStyle(marker_style[2]);
    h_hits_mpd[1]->SetMarkerColor(marker_color[2]);
    h_hits_mpd[1]->SetLineColor(marker_color[2]);
    h_hits_mpd[1]->SetLineWidth(2);
    
    h_hits_mpd[0]->Draw("");
    h_hits_mpd[1]->Draw("SAME");
    leg8->AddEntry(h_hits_mpd[0],"no track cut","l");
    leg8->AddEntry(h_hits_mpd[1],"with track cut","l");
    leg8->Draw();
    
    
    canvas1->SetBottomMargin(0.17);
    canvas1->SetLeftMargin(0.13);
    
    canvas1->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/DCA_full/N_hits_check.png"),"recreate");
    
    TCanvas* c_DCA[3][n_proj];
    TLegend* leg[3];
    TLine* dca_line[2];
    for (Int_t i=0;i<n_proj;i++){
                    
        c_DCA[0][i] = new TCanvas(Form("c_DCA%i%i",0,i),Form("c_DCA%i%i",0,i),700,500);
        c_DCA[0][i]->SetLogy();
        c_DCA[0][i]->cd();
        
        c_DCA[0][i]->SetBottomMargin(0.17);
        c_DCA[0][i]->SetLeftMargin(0.13);
        
        leg[0] = new TLegend(0.15,0.69,0.5,0.87);
        leg[0]->SetBorderSize(0);
        //leg2 = new TLegend(0.5,0.69,0.88,0.87);
        //leg2->SetBorderSize(0);
        
        I_DCA_all[0][i]->GetXaxis()->SetTitleSize(0.08);
        I_DCA_all[0][i]->GetXaxis()->SetLabelSize(0.06);
        I_DCA_all[0][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_all[0][i]->GetYaxis()->SetTitleSize(0.08);
        I_DCA_all[0][i]->GetYaxis()->SetTitleOffset(0.8);    
        I_DCA_all[0][i]->GetYaxis()->SetLabelSize(0.06);
        
        I_DCA_all[0][i]->GetXaxis()->SetRangeUser(-3.,3.);
        I_DCA_all[0][i]->GetYaxis()->SetRangeUser(1.,1e11);
        
        I_DCA_all[0][i]->SetMarkerStyle(marker_style[0]);
        I_DCA_all[0][i]->SetMarkerColor(marker_color[0]);
        I_DCA_all[0][i]->SetLineColor(marker_color[0]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_all[0][i]->SetLineWidth(2);
        
        I_DCA_primary[0][i]->SetMarkerStyle(marker_style[2]);
        I_DCA_primary[0][i]->SetMarkerColor(marker_color[1]);
        I_DCA_primary[0][i]->SetLineColor(marker_color[1]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_primary[0][i]->SetLineWidth(2);
        
        I_DCA_secondary[0][i]->SetMarkerStyle(marker_style[2]);
        I_DCA_secondary[0][i]->SetMarkerColor(marker_color[2]);
        I_DCA_secondary[0][i]->SetLineColor(marker_color[2]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_secondary[0][i]->SetLineWidth(2);
        
        leg[0]->AddEntry(I_DCA_all[0][i],"all","p");
        leg[0]->AddEntry(I_DCA_primary[0][i],"primary","p");
        leg[0]->AddEntry(I_DCA_secondary[0][i],"secondary","p");
        
        //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
        //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
        
        //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
        //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
        
        I_DCA_all[0][i]->Draw("P,E,X0,HIST");
        I_DCA_primary[0][i]->Draw("P,E,X0,SAME,HIST");
        I_DCA_secondary[0][i]->Draw("P,E,X0,SAME,HIST");
        leg[0]->Draw();
        
        c_DCA[0][i]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA/dca_no_chi2_%i_.png",i),"recreate");
        
        c_DCA[1][i] = new TCanvas(Form("c_DCA%i%i",1,i),Form("c_DCA%i%i",1,i),700,500);
        c_DCA[1][i]->SetLogy();
        c_DCA[1][i]->cd();
        
        c_DCA[1][i]->SetBottomMargin(0.17);
        c_DCA[1][i]->SetLeftMargin(0.13);
        
        leg[1] = new TLegend(0.15,0.69,0.5,0.87);
        leg[1]->SetBorderSize(0);
        //leg2 = new TLegend(0.5,0.69,0.88,0.87);
        //leg2->SetBorderSize(0);
        
        I_DCA_all[1][i]->GetXaxis()->SetTitleSize(0.08);
        I_DCA_all[1][i]->GetXaxis()->SetLabelSize(0.06);
        I_DCA_all[1][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_all[1][i]->GetYaxis()->SetTitleSize(0.08);
        I_DCA_all[1][i]->GetYaxis()->SetTitleOffset(0.8);    
        I_DCA_all[1][i]->GetYaxis()->SetLabelSize(0.06);
        
        I_DCA_all[1][i]->GetXaxis()->SetRangeUser(-3.,3.);
        I_DCA_all[1][i]->GetYaxis()->SetRangeUser(1.,1e11);
        
        I_DCA_all[1][i]->SetMarkerStyle(marker_style[0]);
        I_DCA_all[1][i]->SetMarkerColor(marker_color[0]);
        I_DCA_all[1][i]->SetLineColor(marker_color[0]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_all[1][i]->SetLineWidth(2);
        
        I_DCA_primary[1][i]->SetMarkerStyle(marker_style[2]);
        I_DCA_primary[1][i]->SetMarkerColor(marker_color[1]);
        I_DCA_primary[1][i]->SetLineColor(marker_color[1]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_primary[1][i]->SetLineWidth(2);
        
        I_DCA_secondary[1][i]->SetMarkerStyle(marker_style[2]);
        I_DCA_secondary[1][i]->SetMarkerColor(marker_color[2]);
        I_DCA_secondary[1][i]->SetLineColor(marker_color[2]);
        //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
        I_DCA_secondary[1][i]->SetLineWidth(2);
        
        leg[1]->AddEntry(I_DCA_all[1][i],"all","p");
        leg[1]->AddEntry(I_DCA_primary[1][i],"primary","p");
        leg[1]->AddEntry(I_DCA_secondary[1][i],"secondary","p");
        
        //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
        //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
        
        //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
        //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
        
        I_DCA_all[1][i]->Draw("P,E,X0,HIST");
        I_DCA_primary[1][i]->Draw("P,E,X0,SAME,HIST");
        I_DCA_secondary[1][i]->Draw("P,E,X0,SAME,HIST");
        leg[1]->Draw();
        
        c_DCA[1][i]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA/dca_w_chi2_%i_.png",i),"recreate");
        
        c_DCA[2][i] = new TCanvas(Form("c_DCA%i%i",2,i),Form("c_DCA%i%i",2,i),700,500);
        c_DCA[2][i]->cd();
        
        c_DCA[2][i]->SetBottomMargin(0.17);
        c_DCA[2][i]->SetLeftMargin(0.13);
        
        leg[2] = new TLegend(0.15,0.69,0.5,0.87);
        leg[2]->SetBorderSize(0);
        
        I_DCA_cnt[0][i]->GetXaxis()->SetTitleSize(0.08);
        I_DCA_cnt[0][i]->GetXaxis()->SetLabelSize(0.06);
        I_DCA_cnt[0][i]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
        I_DCA_cnt[0][i]->GetYaxis()->SetTitleSize(0.08);
        I_DCA_cnt[0][i]->GetYaxis()->SetTitleOffset(0.8);    
        I_DCA_cnt[0][i]->GetYaxis()->SetLabelSize(0.06);
        
        I_DCA_cnt[0][i]->GetXaxis()->SetRangeUser(-3.,3.);
        I_DCA_cnt[0][i]->GetYaxis()->SetRangeUser(0.,0.5);
        
        I_DCA_cnt[0][i]->SetMarkerStyle(marker_style[0]);
        I_DCA_cnt[0][i]->SetMarkerColor(marker_color[1]);
        I_DCA_cnt[0][i]->SetLineColor(marker_color[1]);
        I_DCA_cnt[0][i]->SetLineWidth(2);
        
        I_DCA_cnt[1][i]->SetMarkerStyle(marker_style[1]);
        I_DCA_cnt[1][i]->SetMarkerColor(marker_color[2]);
        I_DCA_cnt[1][i]->SetLineColor(marker_color[2]);
        I_DCA_cnt[1][i]->SetLineWidth(2);
        
        leg[2]->AddEntry(I_DCA_cnt[0][i],"before #chi^{2} cut","p");
        leg[2]->AddEntry(I_DCA_cnt[1][i],"after #chi^{2} cut","p");
                
        I_DCA_cnt[0][i]->Draw("P,E,X0");
        I_DCA_cnt[1][i]->Draw("P,E,X0,SAME");
        dca_line[0] = new TLine();
        dca_line[0]->SetLineWidth(3.);
        dca_line[0]->SetLineStyle(2); 
        dca_line[0]->DrawLine(-3.,1.,3.,1.);
        dca_line[1] = new TLine();
        dca_line[1]->SetLineStyle(3);
        dca_line[1]->DrawLine(-3.,0.1,3.,0.1);
        leg[2]->Draw();
        
        c_DCA[2][i]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA/purity_dca_%i.png",i),"recreate");
    }
    
    TCanvas* c_DCA_pt[3][n_proj][n_pt_bin];
    TLegend* leg_pt[3];
    TLine* dca_line_pt[2];
    for (Int_t i=0;i<n_proj;i++){
        for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
        
            //if (i_pt != 0) continue;
            //if (i_pt != 3) continue;
            //if (i_pt != 7) continue;
                    
            c_DCA_pt[0][i][i_pt] = new TCanvas(Form("c_DCA_pt%i%i%i",0,i,i_pt),Form("c_DCA_pt%i%i%i%i",0,i,i_pt),700,500);
            c_DCA_pt[0][i][i_pt]->SetLogy();
            c_DCA_pt[0][i][i_pt]->cd();
            
            c_DCA_pt[0][i][i_pt]->SetBottomMargin(0.17);
            c_DCA_pt[0][i][i_pt]->SetLeftMargin(0.13);
            
            leg_pt[0] = new TLegend(0.15,0.69,0.5,0.87);
            leg_pt[0]->SetBorderSize(0);
            //leg2 = new TLegend(0.5,0.69,0.88,0.87);
            //leg2->SetBorderSize(0);
            
            I_DCA_pt_all[0][i][i_pt]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_pt_all[0][i][i_pt]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_pt_all[0][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_pt_all[0][i][i_pt]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_pt_all[0][i][i_pt]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_pt_all[0][i][i_pt]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_pt_all[0][i][i_pt]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_pt_all[0][i][i_pt]->GetYaxis()->SetRangeUser(1.,1e11);
            
            I_DCA_pt_all[0][i][i_pt]->SetMarkerStyle(marker_style[0]);
            I_DCA_pt_all[0][i][i_pt]->SetMarkerColor(marker_color[0]);
            I_DCA_pt_all[0][i][i_pt]->SetLineColor(marker_color[0]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_all[0][i][i_pt]->SetLineWidth(2);
            
            I_DCA_pt_primary[0][i][i_pt]->SetMarkerStyle(marker_style[2]);
            I_DCA_pt_primary[0][i][i_pt]->SetMarkerColor(marker_color[1]);
            I_DCA_pt_primary[0][i][i_pt]->SetLineColor(marker_color[1]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_primary[0][i][i_pt]->SetLineWidth(2);
            
            I_DCA_pt_secondary[0][i][i_pt]->SetMarkerStyle(marker_style[2]);
            I_DCA_pt_secondary[0][i][i_pt]->SetMarkerColor(marker_color[2]);
            I_DCA_pt_secondary[0][i][i_pt]->SetLineColor(marker_color[2]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_secondary[0][i][i_pt]->SetLineWidth(2);
            
            leg_pt[0]->AddEntry(I_DCA_pt_all[0][i][i_pt],"all","p");
            leg_pt[0]->AddEntry(I_DCA_pt_primary[0][i][i_pt],"primary","p");
            leg_pt[0]->AddEntry(I_DCA_pt_secondary[0][i][i_pt],"secondary","p");
            
            //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
            //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
            
            //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            
            I_DCA_pt_all[0][i][i_pt]->Draw("P,E,X0,HIST");
            I_DCA_pt_primary[0][i][i_pt]->Draw("P,E,X0,SAME,HIST");
            I_DCA_pt_secondary[0][i][i_pt]->Draw("P,E,X0,SAME,HIST");
            leg_pt[0]->Draw();
            
            c_DCA_pt[0][i][i_pt]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_pt/dca_no_chi2_%i_%i.png",i,i_pt),"recreate");
            
            c_DCA_pt[1][i][i_pt] = new TCanvas(Form("c_DCA_pt%i%i%i",1,i,i_pt),Form("c_DCA_pt%i%i%i",1,i,i_pt),700,500);
            c_DCA_pt[1][i][i_pt]->SetLogy();
            c_DCA_pt[1][i][i_pt]->cd();
            
            c_DCA_pt[1][i][i_pt]->SetBottomMargin(0.17);
            c_DCA_pt[1][i][i_pt]->SetLeftMargin(0.13);
            
            leg_pt[1] = new TLegend(0.15,0.69,0.5,0.87);
            leg_pt[1]->SetBorderSize(0);
            //leg2 = new TLegend(0.5,0.69,0.88,0.87);
            //leg2->SetBorderSize(0);
            
            I_DCA_pt_all[1][i][i_pt]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_pt_all[1][i][i_pt]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_pt_all[1][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_pt_all[1][i][i_pt]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_pt_all[1][i][i_pt]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_pt_all[1][i][i_pt]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_pt_all[1][i][i_pt]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_pt_all[1][i][i_pt]->GetYaxis()->SetRangeUser(1.,1e11);
            
            I_DCA_pt_all[1][i][i_pt]->SetMarkerStyle(marker_style[0]);
            I_DCA_pt_all[1][i][i_pt]->SetMarkerColor(marker_color[0]);
            I_DCA_pt_all[1][i][i_pt]->SetLineColor(marker_color[0]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_all[1][i][i_pt]->SetLineWidth(2);
            
            I_DCA_pt_primary[1][i][i_pt]->SetMarkerStyle(marker_style[2]);
            I_DCA_pt_primary[1][i][i_pt]->SetMarkerColor(marker_color[1]);
            I_DCA_pt_primary[1][i][i_pt]->SetLineColor(marker_color[1]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_primary[1][i][i_pt]->SetLineWidth(2);
            
            I_DCA_pt_secondary[1][i][i_pt]->SetMarkerStyle(marker_style[2]);
            I_DCA_pt_secondary[1][i][i_pt]->SetMarkerColor(marker_color[2]);
            I_DCA_pt_secondary[1][i][i_pt]->SetLineColor(marker_color[2]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_pt_secondary[1][i][i_pt]->SetLineWidth(2);
            
            leg_pt[1]->AddEntry(I_DCA_pt_all[1][i][i_pt],"all","p");
            leg_pt[1]->AddEntry(I_DCA_pt_primary[1][i][i_pt],"primary","p");
            leg_pt[1]->AddEntry(I_DCA_pt_secondary[1][i][i_pt],"secondary","p");
            
            //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
            //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
            
            //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            
            I_DCA_pt_all[1][i][i_pt]->Draw("P,E,X0,HIST");
            I_DCA_pt_primary[1][i][i_pt]->Draw("P,E,X0,SAME,HIST");
            I_DCA_pt_secondary[1][i][i_pt]->Draw("P,E,X0,SAME,HIST");
            leg_pt[1]->Draw();
            
            c_DCA_pt[1][i][i_pt]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_pt/dca_w_chi2_%i_%i.png",i,i_pt),"recreate");
            
            c_DCA_pt[2][i][i_pt] = new TCanvas(Form("c_DCA_pt%i%i%i",2,i,i_pt),Form("c_DCA_pt%i%i%i%i",2,i,i_pt),700,500);
            c_DCA_pt[2][i][i_pt]->cd();
            
            c_DCA_pt[2][i][i_pt]->SetBottomMargin(0.17);
            c_DCA_pt[2][i][i_pt]->SetLeftMargin(0.13);
            
            leg_pt[2] = new TLegend(0.15,0.69,0.5,0.87);
            leg_pt[2]->SetBorderSize(0);
            
            I_DCA_pt_cnt[0][i][i_pt]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_pt_cnt[0][i][i_pt]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_pt_cnt[0][i][i_pt]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_pt_cnt[0][i][i_pt]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_pt_cnt[0][i][i_pt]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_pt_cnt[0][i][i_pt]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_pt_cnt[0][i][i_pt]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_pt_cnt[0][i][i_pt]->GetYaxis()->SetRangeUser(0.,0.5);
            
            I_DCA_pt_cnt[0][i][i_pt]->SetMarkerStyle(marker_style[0]);
            I_DCA_pt_cnt[0][i][i_pt]->SetMarkerColor(marker_color[1]);
            I_DCA_pt_cnt[0][i][i_pt]->SetLineColor(marker_color[1]);
            I_DCA_pt_cnt[0][i][i_pt]->SetLineWidth(2);
            
            I_DCA_pt_cnt[1][i][i_pt]->SetMarkerStyle(marker_style[1]);
            I_DCA_pt_cnt[1][i][i_pt]->SetMarkerColor(marker_color[2]);
            I_DCA_pt_cnt[1][i][i_pt]->SetLineColor(marker_color[2]);
            I_DCA_pt_cnt[1][i][i_pt]->SetLineWidth(2);
            
            leg_pt[2]->AddEntry(I_DCA_pt_cnt[0][i][i_pt],"before #chi^{2} cut","p");
            leg_pt[2]->AddEntry(I_DCA_pt_cnt[1][i][i_pt],"after #chi^{2} cut","p");
                    
            I_DCA_pt_cnt[0][i][i_pt]->Draw("P,E,X0");
            I_DCA_pt_cnt[1][i][i_pt]->Draw("P,E,X0,SAME");
            dca_line_pt[0] = new TLine();
            dca_line_pt[0]->SetLineWidth(3.);
            dca_line_pt[0]->SetLineStyle(2); 
            dca_line_pt[0]->DrawLine(-3.,1.,3.,1.);
            dca_line_pt[1] = new TLine();
            dca_line_pt[1]->SetLineStyle(3);
            dca_line_pt[1]->DrawLine(-3.,0.1,3.,0.1);
            leg_pt[2]->Draw();
            
            c_DCA_pt[2][i][i_pt]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_pt/purity_dca_%i_%i.png",i,i_pt),"recreate");
        }
    }
    
    TCanvas* c_DCA_eta[3][n_proj][n_eta_bin];
    TLegend* leg_eta[3];
    TLine* dca_line_eta[2];
    for (Int_t i=0;i<n_proj;i++){
        for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
        
            //if (i_pt != 0) continue;
            //if (i_pt != 3) continue;
            //if (i_pt != 7) continue;
                    
            c_DCA_eta[0][i][i_eta] = new TCanvas(Form("c_DCA_eta%i%i%i",0,i,i_eta),Form("c_DCA_eta%i%i%i%i",0,i,i_eta),700,500);
            c_DCA_eta[0][i][i_eta]->SetLogy();
            c_DCA_eta[0][i][i_eta]->cd();
            
            c_DCA_eta[0][i][i_eta]->SetBottomMargin(0.17);
            c_DCA_eta[0][i][i_eta]->SetLeftMargin(0.13);
            
            leg_eta[0] = new TLegend(0.15,0.69,0.5,0.87);
            leg_eta[0]->SetBorderSize(0);
            //leg2 = new TLegend(0.5,0.69,0.88,0.87);
            //leg2->SetBorderSize(0);
            
            I_DCA_eta_all[0][i][i_eta]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_eta_all[0][i][i_eta]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_eta_all[0][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_eta_all[0][i][i_eta]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_eta_all[0][i][i_eta]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_eta_all[0][i][i_eta]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_eta_all[0][i][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_eta_all[0][i][i_eta]->GetYaxis()->SetRangeUser(1.,1e11);
            
            I_DCA_eta_all[0][i][i_eta]->SetMarkerStyle(marker_style[0]);
            I_DCA_eta_all[0][i][i_eta]->SetMarkerColor(marker_color[0]);
            I_DCA_eta_all[0][i][i_eta]->SetLineColor(marker_color[0]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_all[0][i][i_eta]->SetLineWidth(2);
            
            I_DCA_eta_primary[0][i][i_eta]->SetMarkerStyle(marker_style[2]);
            I_DCA_eta_primary[0][i][i_eta]->SetMarkerColor(marker_color[1]);
            I_DCA_eta_primary[0][i][i_eta]->SetLineColor(marker_color[1]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_primary[0][i][i_eta]->SetLineWidth(2);
            
            I_DCA_eta_secondary[0][i][i_eta]->SetMarkerStyle(marker_style[2]);
            I_DCA_eta_secondary[0][i][i_eta]->SetMarkerColor(marker_color[2]);
            I_DCA_eta_secondary[0][i][i_eta]->SetLineColor(marker_color[2]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_secondary[0][i][i_eta]->SetLineWidth(2);
            
            leg_eta[0]->AddEntry(I_DCA_eta_all[0][i][i_eta],"all","p");
            leg_eta[0]->AddEntry(I_DCA_eta_primary[0][i][i_eta],"primary","p");
            leg_eta[0]->AddEntry(I_DCA_eta_secondary[0][i][i_eta],"secondary","p");
            
            //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
            //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
            
            //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            
            I_DCA_eta_all[0][i][i_eta]->Draw("P,E,X0,HIST");
            I_DCA_eta_primary[0][i][i_eta]->Draw("P,E,X0,SAME,HIST");
            I_DCA_eta_secondary[0][i][i_eta]->Draw("P,E,X0,SAME,HIST");
            leg_eta[0]->Draw();
            
            c_DCA_eta[0][i][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_eta/dca_no_chi2_%i_%i.png",i,i_eta),"recreate");
            
            c_DCA_eta[1][i][i_eta] = new TCanvas(Form("c_DCA_eta%i%i%i",1,i,i_eta),Form("c_DCA_eta%i%i%i",1,i,i_eta),700,500);
            c_DCA_eta[1][i][i_eta]->SetLogy();
            c_DCA_eta[1][i][i_eta]->cd();
            
            c_DCA_eta[1][i][i_eta]->SetBottomMargin(0.17);
            c_DCA_eta[1][i][i_eta]->SetLeftMargin(0.13);
            
            leg_eta[1] = new TLegend(0.15,0.69,0.5,0.87);
            leg_eta[1]->SetBorderSize(0);
            //leg2 = new TLegend(0.5,0.69,0.88,0.87);
            //leg2->SetBorderSize(0);
            
            I_DCA_eta_all[1][i][i_eta]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_eta_all[1][i][i_eta]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_eta_all[1][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_eta_all[1][i][i_eta]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_eta_all[1][i][i_eta]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_eta_all[1][i][i_eta]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_eta_all[1][i][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_eta_all[1][i][i_eta]->GetYaxis()->SetRangeUser(1.,1e11);
            
            I_DCA_eta_all[1][i][i_eta]->SetMarkerStyle(marker_style[0]);
            I_DCA_eta_all[1][i][i_eta]->SetMarkerColor(marker_color[0]);
            I_DCA_eta_all[1][i][i_eta]->SetLineColor(marker_color[0]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_all[1][i][i_eta]->SetLineWidth(2);
            
            I_DCA_eta_primary[1][i][i_eta]->SetMarkerStyle(marker_style[2]);
            I_DCA_eta_primary[1][i][i_eta]->SetMarkerColor(marker_color[1]);
            I_DCA_eta_primary[1][i][i_eta]->SetLineColor(marker_color[1]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_primary[1][i][i_eta]->SetLineWidth(2);
            
            I_DCA_eta_secondary[1][i][i_eta]->SetMarkerStyle(marker_style[2]);
            I_DCA_eta_secondary[1][i][i_eta]->SetMarkerColor(marker_color[2]);
            I_DCA_eta_secondary[1][i][i_eta]->SetLineColor(marker_color[2]);
            //h_dca_all[0][i][i_pt][i_eta]->SetMarkerSize(2.);
            I_DCA_eta_secondary[1][i][i_eta]->SetLineWidth(2);
            
            leg_eta[1]->AddEntry(I_DCA_pt_all[1][i][i_eta],"all","p");
            leg_eta[1]->AddEntry(I_DCA_pt_primary[1][i][i_eta],"primary","p");
            leg_eta[1]->AddEntry(I_DCA_pt_secondary[1][i][i_eta],"secondary","p");
            
            //leg2->AddEntry(h_dca_all[0][i][i_pt][i_eta],"before #chi^{2} cut","p");
            //leg2->AddEntry(h_dca_all[1][i][i_pt][i_eta],"after #chi^{2} cut","p");
            
            //h_dca_all[0][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",0,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            //h_dca_all[1][i][i_pt][i_eta]->GetFunction(Form("f_dca_all%i%i%i%i",1,i,i_pt,i_eta))->SetBit(TF1::kNotDraw);
            
            I_DCA_eta_all[1][i][i_eta]->Draw("P,E,X0,HIST");
            I_DCA_eta_primary[1][i][i_eta]->Draw("P,E,X0,SAME,HIST");
            I_DCA_eta_secondary[1][i][i_eta]->Draw("P,E,X0,SAME,HIST");
            leg_eta[1]->Draw();
            
            c_DCA_eta[1][i][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_eta/dca_w_chi2_%i_%i.png",i,i_eta),"recreate");
            
            c_DCA_eta[2][i][i_eta] = new TCanvas(Form("c_DCA_eta%i%i%i",2,i,i_eta),Form("c_DCA_eta%i%i%i%i",2,i,i_eta),700,500);
            c_DCA_eta[2][i][i_eta]->cd();
            
            c_DCA_eta[2][i][i_eta]->SetBottomMargin(0.17);
            c_DCA_eta[2][i][i_eta]->SetLeftMargin(0.13);
            
            leg_eta[2] = new TLegend(0.15,0.69,0.5,0.87);
            leg_eta[2]->SetBorderSize(0);
            
            I_DCA_eta_cnt[0][i][i_eta]->GetXaxis()->SetTitleSize(0.08);
            I_DCA_eta_cnt[0][i][i_eta]->GetXaxis()->SetLabelSize(0.06);
            I_DCA_eta_cnt[0][i][i_eta]->GetXaxis()->SetTitle(Form("DCA %s",s_proj[i].Data()));
            I_DCA_eta_cnt[0][i][i_eta]->GetYaxis()->SetTitleSize(0.08);
            I_DCA_eta_cnt[0][i][i_eta]->GetYaxis()->SetTitleOffset(0.8);    
            I_DCA_eta_cnt[0][i][i_eta]->GetYaxis()->SetLabelSize(0.06);
            
            I_DCA_eta_cnt[0][i][i_eta]->GetXaxis()->SetRangeUser(-3.,3.);
            I_DCA_eta_cnt[0][i][i_eta]->GetYaxis()->SetRangeUser(0.,0.5);
            
            I_DCA_eta_cnt[0][i][i_eta]->SetMarkerStyle(marker_style[0]);
            I_DCA_eta_cnt[0][i][i_eta]->SetMarkerColor(marker_color[1]);
            I_DCA_eta_cnt[0][i][i_eta]->SetLineColor(marker_color[1]);
            I_DCA_eta_cnt[0][i][i_eta]->SetLineWidth(2);
            
            I_DCA_eta_cnt[1][i][i_eta]->SetMarkerStyle(marker_style[1]);
            I_DCA_eta_cnt[1][i][i_eta]->SetMarkerColor(marker_color[2]);
            I_DCA_eta_cnt[1][i][i_eta]->SetLineColor(marker_color[2]);
            I_DCA_eta_cnt[1][i][i_eta]->SetLineWidth(2);
            
            leg_eta[2]->AddEntry(I_DCA_eta_cnt[0][i][i_eta],"before #chi^{2} cut","p");
            leg_eta[2]->AddEntry(I_DCA_eta_cnt[1][i][i_eta],"after #chi^{2} cut","p");
                    
            I_DCA_eta_cnt[0][i][i_eta]->Draw("P,E,X0");
            I_DCA_eta_cnt[1][i][i_eta]->Draw("P,E,X0,SAME");
            dca_line_eta[0] = new TLine();
            dca_line_eta[0]->SetLineWidth(3.);
            dca_line_eta[0]->SetLineStyle(2); 
            dca_line_eta[0]->DrawLine(-3.,1.,3.,1.);
            dca_line_eta[1] = new TLine();
            dca_line_eta[1]->SetLineStyle(3);
            dca_line_eta[1]->DrawLine(-3.,0.1,3.,0.1);
            leg_eta[2]->Draw();
            
            c_DCA_eta[2][i][i_eta]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/TDR/DCA_eta/purity_dca_%i_%i.png",i,i_eta),"recreate");
        }
    }
    
    
}
