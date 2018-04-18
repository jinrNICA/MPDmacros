void make_dca_cut()
{
        cout << "Starting..." << endl;
        TFile* file = new TFile("~/Desktop/merged_1M.root","read");
        
        const Float_t pt_bins[]={0.,0.5,1.0,2.0};
        const Float_t eta_bins[]={0.,1.,2.5};
        const TString s_proj[]={TString("x"),TString("y"),TString("z")};
        const Int_t n_pt_bin = 3;
        const Int_t n_eta_bin = 2;
        const Int_t n_proj = 3;
        const Int_t n_cut = 2;

        TH1F *h_dca_all[n_cut][n_proj][n_pt_bin][n_eta_bin];
        TH1F *h_dca_primary[n_cut][n_proj][n_pt_bin][n_eta_bin];
        TH1F *h_dca_secondary[n_cut][n_proj][n_pt_bin][n_eta_bin];
        
        TF1  *f_dca_all[n_cut][n_proj][n_pt_bin][n_eta_bin];
        TF1  *f_dca_primary[n_cut][n_proj][n_pt_bin][n_eta_bin];
        TF1  *f_dca_secondary[n_cut][n_proj][n_pt_bin][n_eta_bin];
        
        cout << "Initializing..." << endl;
        for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
            for (Int_t i=0;i<n_proj;i++){
                for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
                    for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                        h_dca_all[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta));
                        h_dca_primary[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta));
                        h_dca_secondary[i_cut][i][i_pt][i_eta] = (TH1F*) file->Get(Form("h_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    
                        f_dca_all[i_cut][i][i_pt][i_eta] = new TF1(Form("f_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta),"gaus",-10.,10.);
                        f_dca_primary[i_cut][i][i_pt][i_eta] = new TF1(Form("f_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta),"gaus",-10.,10.);
                        f_dca_secondary[i_cut][i][i_pt][i_eta] = new TF1(Form("f_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta),"gaus",-10.,10.);
                    }
                }
            }
        }
        
        cout << "Fitting..." << endl;
        for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
            for (Int_t i=0;i<n_proj;i++){
                for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
                    for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                        h_dca_all[i_cut][i][i_pt][i_eta]->Fit(Form("f_dca_all%i%i%i%i",i_cut,i,i_pt,i_eta));
                        h_dca_primary[i_cut][i][i_pt][i_eta]->Fit(Form("f_dca_primary%i%i%i%i",i_cut,i,i_pt,i_eta));
                        h_dca_secondary[i_cut][i][i_pt][i_eta]->Fit(Form("f_dca_secondary%i%i%i%i",i_cut,i,i_pt,i_eta));
                    }
                }
            }
        }
        
        cout << "Saving output..." << endl;
        TFile* outfile = new TFile("~/Desktop/dca_fit_1M.root","recreate");
        outfile->cd();
        for (Int_t i_cut=0;i_cut<n_cut;i_cut++){
            for (Int_t i=0;i<n_proj;i++){
                for (Int_t i_pt=0;i_pt<n_pt_bin;i_pt++){
                    for (Int_t i_eta=0;i_eta<n_eta_bin;i_eta++){
                        h_dca_all[i_cut][i][i_pt][i_eta]->Write();
                        h_dca_primary[i_cut][i][i_pt][i_eta]->Write();
                        h_dca_secondary[i_cut][i][i_pt][i_eta]->Write();
                    
                        f_dca_all[i_cut][i][i_pt][i_eta]->Write();
                        f_dca_primary[i_cut][i][i_pt][i_eta]->Write();
                        f_dca_secondary[i_cut][i][i_pt][i_eta]->Write();
                    }
                }
            }
        }
        outfile->Close();
}
