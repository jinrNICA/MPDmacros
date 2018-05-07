const Int_t n_harm       = 2;
const Int_t n_energy     = 1;
const Int_t n_sorts      = 3;
const Int_t n_centrality = 2;
const Int_t n_proj       = 3;
const Int_t marker_res_style[]={24,20,26,22};
const Int_t marker_flow_stl[2][3] ={{20,21,22},{24,25,26}};
const Int_t marker_dca_style[]={20,21,22};
const Int_t marker_eff_style[]={20,22,24,26};
const Int_t marker_res_color[]={1,2,4,2};
const Int_t marker_eff_color[]={4,8};
const Int_t line_pt_style[]   ={1,2,9};

const Float_t latex_coord[]     ={0.49,0.85};
const TString latex_title       =TString("Au+Au, #sqrt{s_{NN}}=11 GeV, GEANT3, UrQMD, 4M events");
const TString vn_Title[]        = {TString("Au-Au, #sqrt{s_{NN}}=11 GeV, 10-20%, GEANT3, UrQMD"), TString("Au-Au, #sqrt{s_{NN}}=11 GeV, 20-40%, GEANT3, UrQMD")};

const Float_t range_vn_pt[2][2]      ={{-0.042,0.078},{0.,0.099}};
const Float_t range_vn_rapidity[2][2]={{-0.22,0.22},{0.,0.099}};
const Float_t rapidity_range[]       ={-1.4,1.4};
const Float_t pt_range[]             ={0.21,2.};
const Float_t pt_track_range[]       ={0.,3.1};
const Float_t eta_track_range[]      ={-1.9,1.9};
const Float_t res_range[2][2]        ={{0.21,1.19},{0.01,0.96}};
const Float_t vn_cent_range[2][2]    ={{-0.07,0.01},{-0.035,0.045}};
const Float_t dca_x_range[]          ={-3.1,3.1};
const Float_t mult_range[]           ={0,1800};
const Int_t   n_hits_range[]         ={0,59};
const Int_t   centrality_range[]     ={0,79};

const double range_dca[]={1e5,2e8};

const TString energy_title[]={TString("11 GeV"),TString("11 GeV")};
const TString pid_title[]={TString("p"),TString("K"),TString("#pi")};
const TString proj_title[]={TString("x"),TString("y"),TString("z")};

const Float_t centralityBinsRes[] = {0.,5.,10.,15.,20.,25.,30.,35.,40.,45.,50.,55.,60.,65.,70.,75.,80.,85.,90.,95.,100};
const Int_t NcentralityBinsRes = 20;

const float ptBins[] = {0.,0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.5, 3.};
const int NptBins = 12;

const float etaBins[] = {-1.5,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.5};
const int NetaBins = 14;

void Draw_TDR_clone()
{
    
    gROOT->ForceStyle();

    char name[200];
    char title[200];

    TFile* in_flow_file[n_energy][n_sorts];
    TFile* in_res_true_file[n_energy];
    TFile* in_res_true_file_HP[n_energy];
    TFile* in_res_reco_file[n_energy];

    TFile* in_res_laqgsm_file = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/LAQGSM.root","read");

    //in_res_true_file[0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-5-gev.root","read");
    //in_res_true_file_HP[0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-5-gev_HP.root","read");
    //in_res_reco_file[0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-fit-5-gev.root","read");
    in_res_true_file[0] = new TFile("/home/peter/res_hist-11gev-4M.root","read");
    //in_res_true_file_HP[0] = new TFile("/home/peter/res_hist-11gev.root","read");
    in_res_reco_file[0] = new TFile("/home/peter/res-fit-11gev-4M.root","read");
    //in_res_true_file[1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-11-gev.root","read");
    //in_res_true_file[1] = new TFile("/home/peter/res_hist-11gev.root","read");
    ////in_res_true_file_HP[1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-11-gev_HP.root","read");
    //in_res_true_file_HP[1] = new TFile("/home/peter/res_hist-11gev.root","read");
    ////in_res_reco_file[1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res-fit-11-gev.root","read");
    //in_res_reco_file[1] = new TFile("/home/peter/res-fit-11gev.root","read");

    //in_flow_file[0][0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-5-gev-proton.root","read");
    //in_flow_file[0][1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-5-gev-kaon.root","read");
    //in_flow_file[0][2] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-5-gev-pion.root","read");
    in_flow_file[0][0] = new TFile("/home/peter/flow-11gev-protons4M.root","read");
    in_flow_file[0][1] = new TFile("/home/peter/flow-11gev-kaons4M.root","read");
    in_flow_file[0][2] = new TFile("/home/peter/flow-11gev-pions4M.root","read");
    //in_flow_file[1][0] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-proton.root","read");
    //in_flow_file[1][0] = new TFile("/home/peter/flow-11gev-protons_noBirkPDG.root","read");
    ////in_flow_file[1][1] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-kaon.root","read");
    //in_flow_file[1][1] = new TFile("/home/peter/flow-11gev-kaons_noBirkPDG.root","read");
    ////in_flow_file[1][2] = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/flow-11-gev-pion.root","read");
    //in_flow_file[1][2] = new TFile("/home/peter/flow-11gev-pions_noBirkPDG.root","read");
    
    TFile* inStyle = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/my_style.root","READ");
    
    TStyle* style = (TStyle*) inStyle->Get("style");
    
    //TStyle* style = new TStyle("Default","Default style");
    //style->SetTitleSize(0.05,"X");
    //style->SetTitleSize(0.05,"Y");
    //style->SetTitleOffset(1.15,"Y");
    //style->SetTitleOffset(0.9,"X");
    //style->SetFrameLineWidth(2);
    //style->SetFrameFillColor(0);
    //style->SetPadColor(0);
    //style->SetLabelSize(0.04,"X");
    //style->SetLabelSize(0.04,"Y");
    //style->SetPadTopMargin(0.1);
    //style->SetPadBottomMargin(0.12);
    //style->SetPadLeftMargin(0.12);
    //style->SetPadTopMargin(0.02);
    //style->SetPadRightMargin(0.03);
    //style->SetMarkerSize(1.2);
    //style->SetErrorX(0);
    //style->SetOptStat(0);
    //style->SetCanvasColor(0);
    //style->SetTitleFillColor(0);
    //style->SetTitleBorderSize(0);
    //style->SetCanvasBorderMode(0);
    //style->SetLegendBorderSize(0);
    //style->SetPadBorderMode(0);
    //style->SetLineWidth(2);

    style->cd();
    
    gStyle->SetPalette(1);
    
    //TFile* inFlowFile = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/output_final_dca_centrality.root","READ");
    
    //TFile* inResFile = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/TDR/res_calibrate.root","READ");

    TH1F*     h_n_hits_before[n_energy];
    TH1F*     h_n_hits_after[n_energy];

    TH1F*     h_mult[n_energy];

    TH2       *h2_b_vs_centrality[n_energy];
    TProfile  *p_resolution_vs_centrality[n_energy];

    TH1F*     h_DCA_in_all[n_energy][n_proj][NptBins][NetaBins];
    TH1F*     h_DCA_in_primary[n_energy][n_proj][NptBins][NetaBins];
    TH1F*     h_DCA_in_secondary[n_energy][n_proj][NptBins][NetaBins];

    TH1F*     h_DCA_all[n_energy][n_proj];
    TH1F*     h_DCA_primary[n_energy][n_proj];
    TH1F*     h_DCA_secondary[n_energy][n_proj];

    TH1F*     h_contam[n_energy][n_proj];

    TH1F*     h_pt_reco_in_before[n_energy][n_centrality][n_sorts+1];
    TH1F*     h_pt_true_in_before[n_energy][n_centrality][n_sorts+1];
    TH1F*     h_pt_reco_in_after[n_energy][n_centrality][n_sorts+1];
    TH1F*     h_pt_true_in_after[n_energy][n_centrality][n_sorts+1];

    TH1F*     h_pt_reco_in_after_HP[n_energy][n_centrality][n_sorts+1];
    TH1F*     h_pt_true_in_after_HP[n_energy][n_centrality][n_sorts+1];


    TH1F*     h_eta_reco_in_before[n_energy][n_centrality][n_sorts+1];
    TH1F*     h_eta_reco_in_after[n_energy][n_centrality][n_sorts+1];

    TH1F*     h_pt_reco_before[n_energy][n_sorts+1];
    TH1F*     h_pt_true_before[n_energy][n_sorts+1];
    TH1F*     h_pt_reco_after[n_energy][n_sorts+1];
    TH1F*     h_pt_true_after[n_energy][n_sorts+1];

    TH1F*     h_pt_reco_after_HP[n_energy][n_sorts+1];
    TH1F*     h_pt_true_after_HP[n_energy][n_sorts+1];

    TH1F*     h_eta_reco_before[n_energy][n_sorts+1];
    TH1F*     h_eta_reco_after[n_energy][n_sorts+1];

    TH1F*     h_pt_eff_before[n_energy][n_sorts+1];
    TH1F*     h_pt_eff_after[n_energy][n_sorts+1];

    TH1F*     h_pt_eff_after_HP[n_energy][n_sorts+1];
    
    TProfile* p_res_vs_centrality[n_energy][n_harm];
    TH1F*     h_res_vs_centrality[n_energy][n_harm];

    TH1F*     p_res_laqgsm_vs_centrality[n_harm];
    TH1F*     h_res_laqgsm_vs_centrality[n_harm];

    TProfile* p_vn_vs_centrality[n_energy][n_harm][n_sorts];
    TProfile* h_vn_vs_centrality[n_energy][n_harm][n_sorts];

    TProfile* p_vn_vs_centrality_true[n_energy][n_harm];
    TProfile* p_vn_vs_centrality_reco[n_energy][n_harm];

    TProfile* p_vn_true_vs_pt[n_energy][n_harm][n_centrality][n_sorts];
    TProfile* p_vn_reco_vs_pt[n_energy][n_harm][n_centrality][n_sorts];

    TProfile* p_vn_true_vs_rapidity[n_energy][n_harm][n_centrality][n_sorts];
    TProfile* p_vn_reco_vs_rapidity[n_energy][n_harm][n_centrality][n_sorts];



    //GET HISTOGRAMS FROM FILES
    //--------------------------------------------------------------------------------------------------------
    for (Int_t i_harm=0; i_harm<n_harm; i_harm++){
        p_res_laqgsm_vs_centrality[i_harm] = (TH1F*) in_res_laqgsm_file->Get(Form("p_ResPsi_vs_b_flipped[%i][%i][%i]",i_harm,0,1));
        p_res_laqgsm_vs_centrality[i_harm]->SetName(Form("p_res_laqgsm_vs_centrality%i",i_harm));
        h_res_laqgsm_vs_centrality[i_harm] = (TH1F*) in_res_laqgsm_file->Get(Form("p_true_Res_vs_b_flipped[%i][%i][%i]",i_harm,0,1));
        h_res_laqgsm_vs_centrality[i_harm]->SetName(Form("h_res_laqgsm_vs_centrality%i",i_harm));
    }

    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        h_n_hits_before[i_energy] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_nhits_TPC"));
        h_n_hits_before[i_energy]->SetName(Form("h_n_hits_before%i",i_energy));
        h_n_hits_after[i_energy] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_nhits_TPC_after"));
        h_n_hits_after[i_energy]->SetName(Form("h_n_hits_after%i",i_energy));

        h_mult[i_energy] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_multiplicity_before"));
        h_mult[i_energy]->SetName(Form("h_mult%i",i_energy));

        h2_b_vs_centrality[i_energy] = (TH2F*) in_res_true_file[i_energy]->Get("h2_b_vs_centrality");
        h2_b_vs_centrality[i_energy]->SetName(Form("h2_b_vs_centrality%i",i_energy));
        p_resolution_vs_centrality[i_energy] = new TProfile(Form("h_resolution_vs_centrality%i",i_energy)," ;Centrality, %;#sigma_{b}/b;",100,0,100);

        for (Int_t i_proj=0;i_proj<n_proj;i_proj++){

            h_DCA_all[i_energy][i_proj] = new TH1F(Form("h_DCA_all%i%i",i_energy,i_proj),Form(" ;DCA_{%s};N_{count}",proj_title[i_proj].Data()),200,-50,50);
            h_DCA_all[i_energy][i_proj]->Sumw2(); 
            h_DCA_primary[i_energy][i_proj] = new TH1F(Form("h_DCA_primary%i%i",i_energy,i_proj),Form(" ;DCA_{%s};N_{count}",proj_title[i_proj].Data()),200,-50,50);
            h_DCA_primary[i_energy][i_proj]->Sumw2();
            h_DCA_secondary[i_energy][i_proj] = new TH1F(Form("h_DCA_secondary%i%i",i_energy,i_proj),Form(" ;DCA_{%s};N_{count}",proj_title[i_proj].Data()),200,-50,50);
            h_DCA_secondary[i_energy][i_proj]->Sumw2();

            h_contam[i_energy][i_proj] = new TH1F(Form("h_contam%i%i",i_energy,i_proj),Form(" ;DCA;Contamination;",proj_title[i_proj].Data()),200,-50,50);

            for (Int_t i_pt=0;i_pt<NptBins;i_pt++){
                for (Int_t i_eta=0;i_eta<NetaBins;i_eta++){
                    h_DCA_in_all[i_energy][i_proj][i_pt][i_eta] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_DCA_all[%i][%i][%i]",i_proj,i_pt,i_eta));
                    h_DCA_in_all[i_energy][i_proj][i_pt][i_eta]->SetName(Form("h_DCA_in_all%i%i%i%i",i_energy,i_proj,i_pt,i_eta));
                    h_DCA_in_primary[i_energy][i_proj][i_pt][i_eta] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_DCA_primary[%i][%i][%i]",i_proj,i_pt,i_eta));
                    h_DCA_in_primary[i_energy][i_proj][i_pt][i_eta]->SetName(Form("h_DCA_in_primary%i%i%i%i",i_energy,i_proj,i_pt,i_eta));
                    h_DCA_in_secondary[i_energy][i_proj][i_pt][i_eta] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_DCA_secondary[%i][%i][%i]",i_proj,i_pt,i_eta));
                    h_DCA_in_secondary[i_energy][i_proj][i_pt][i_eta]->SetName(Form("h_DCA_in_secondary%i%i%i%i",i_energy,i_proj,i_pt,i_eta));
                }
            }
        }

        for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
            h_pt_reco_before[i_energy][i_sort] = new TH1F(Form("h_pt_reco_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
            h_pt_true_before[i_energy][i_sort] = new TH1F(Form("h_pt_true_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
            h_pt_reco_after[i_energy][i_sort] = new TH1F(Form("h_pt_reco_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
            h_pt_true_after[i_energy][i_sort] = new TH1F(Form("h_pt_true_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
            h_pt_reco_after_HP[i_energy][i_sort] = new TH1F(Form("h_pt_reco_after_HP%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);
            h_pt_true_after_HP[i_energy][i_sort] = new TH1F(Form("h_pt_true_after_HP%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;dN/dp_{T};"),100,0.,3.5);

            h_eta_reco_before[i_energy][i_sort] = new TH1F(Form("h_eta_reco_before%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);
            h_eta_reco_after[i_energy][i_sort] = new TH1F(Form("h_eta_reco_after%i%i",i_energy,i_sort),Form(" ;#eta;dN/d#eta;"),100,-2.,2.);

            h_pt_eff_before[i_energy][i_sort] = new TH1F(Form("h_pt_eff_before%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;Efficiency;"),100,0.,3.5);
            h_pt_eff_after[i_energy][i_sort] = new TH1F(Form("h_pt_eff_after%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;Efficiency;"),100,0.,3.5);

            h_pt_eff_after_HP[i_energy][i_sort] = new TH1F(Form("h_pt_eff_after_HP%i%i",i_energy,i_sort),Form(" ;p_{T}, GeV/c;Efficiency;"),100,0.,3.5);
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

                //h_pt_reco_in_after_HP[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file_HP[i_energy]->Get(Form("h_pt_after[%i][%i]",i_cent,i_sort));
                //h_pt_reco_in_after_HP[i_energy][i_cent][i_sort]->SetName(Form("h_pt_reco_in_after_HP%i%i%i",i_energy,i_cent,i_sort));
                //h_pt_true_in_after_HP[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file_HP[i_energy]->Get(Form("h_pt_mc_after[%i][%i]",i_cent,i_sort));
                //h_pt_reco_in_after_HP[i_energy][i_cent][i_sort]->SetName(Form("h_pt_reco_in_after_HP%i%i%i",i_energy,i_cent,i_sort));

                h_eta_reco_in_before[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta[%i][%i]",i_cent,i_sort));
                h_eta_reco_in_before[i_energy][i_cent][i_sort]->SetName(Form("h_eta_reco_in_before%i%i%i",i_energy,i_cent,i_sort));
                h_eta_reco_in_after[i_energy][i_cent][i_sort] = (TH1F*) in_res_true_file[i_energy]->Get(Form("h_eta_after[%i][%i]",i_cent,i_sort));
                h_eta_reco_in_after[i_energy][i_cent][i_sort]->SetName(Form("h_eta_reco_in_after%i%i%i",i_energy,i_cent,i_sort));
            }
        }

        for (Int_t i_harm=0; i_harm<n_harm; i_harm++){
            //p_res_vs_centrality[0][i_harm] = (TProfile*) inResFile->Get(Form("p_true_Res_vs_b%i%i%i",i_harm,0,3));
            //h_res_vs_centrality[0][i_harm] = (TH1F*)     inResFile->Get(Form("h_Res_out%i",i_harm));
            
            //p_res_vs_centrality[0][i_harm] = (TProfile*) inResFile->Get(Form("p_true_Res_vs_b%i%i%i",i_harm,0,3));

            p_res_vs_centrality[i_energy][i_harm] = (TProfile*) in_res_true_file[i_energy]->Get(Form("p_true_Res_vs_b[%i][%i][%i]",i_harm,0,1));
            p_res_vs_centrality[i_energy][i_harm]->SetName(Form("p_res_vs_centrality%i%i",i_energy,i_harm));
            h_res_vs_centrality[i_energy][i_harm] = (TH1F*)     in_res_reco_file[i_energy]->Get(Form("p_ResPsi_vs_b[%i][%i][%i]",i_harm,0,1));
            h_res_vs_centrality[i_energy][i_harm]->SetName(Form("h_res_vs_centrality%i%i",i_energy,i_harm));

            sprintf(name,"p_vn_vs_centrality_true[%i][%i]",i_energy,i_harm);
            sprintf(title,"v_{%i};Centrality, %;",i_harm+1);
            p_vn_vs_centrality_true[i_energy][i_harm] = new TProfile(name,title,NcentralityBinsRes,centralityBinsRes);

            sprintf(name,"p_vn_vs_centrality_reco[%i][%i]",i_energy,i_harm);
            sprintf(title,"v_{%i};Centrality, %;",i_harm+1);
            p_vn_vs_centrality_reco[i_energy][i_harm] = new TProfile(name,title,NcentralityBinsRes,centralityBinsRes);

            for (Int_t i_sort=0;i_sort<n_sorts;i_sort++){
                h_vn_vs_centrality[i_energy][i_harm][i_sort] = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_full_vs_centrality_divided[%i][%i][%i]",i_harm,0,1));
                h_vn_vs_centrality[i_energy][i_harm][i_sort]->SetName(Form("h_vn_vs_centrality",i_energy,i_harm,i_sort));
                p_vn_vs_centrality[i_energy][i_harm][i_sort] = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_RP_vs_centrality[%i]",i_harm));
                p_vn_vs_centrality[i_energy][i_harm][i_sort]->SetName(Form("p_vn_vs_centrality",i_energy,i_harm,i_sort));

                for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_full_vs_pt_divided[%i][%i][%i][%i]"      ,i_cent,i_harm,0,1));
                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]      ->SetName(Form("p_vn_reco_vs_pt%i%i%i%i",i_energy,i_harm,i_cent,i_sort));
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_full_vs_rapidity_divided[%i][%i][%i][%i]",i_cent,i_harm,0,1));
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort]->SetName(Form("p_vn_reco_vs_rapidity%i%i%i%i",i_energy,i_harm,i_cent,i_sort));

                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_RP_vs_pt[%i][%i]"      ,i_cent,i_harm));
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]      ->SetName(Form("p_vn_true_vs_pt%i%i%i%i",i_energy,i_harm,i_cent,i_sort));
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] = (TProfile*) in_flow_file[i_energy][i_sort]->Get(Form("p_flow_wrt_RP_vs_rapidity[%i][%i]",i_cent,i_harm));
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort]->SetName(Form("p_vn_true_vs_rapidity%i%i%i%i",i_energy,i_harm,i_cent,i_sort));
                }
            }
            
        }
    }
    //--------------------------------------------------------------------------------------------------------
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        p_resolution_vs_centrality[i_energy]->SetMarkerStyle(marker_res_style[i_energy]);
        for (Int_t i_proj=0;i_proj<n_proj;i_proj++){

            h_DCA_all[i_energy][i_proj]->SetMarkerStyle(marker_dca_style[0]);
            h_DCA_primary[i_energy][i_proj]->SetMarkerStyle(marker_dca_style[1]);
            h_DCA_secondary[i_energy][i_proj]->SetMarkerStyle(marker_dca_style[2]);

            h_contam[i_energy][i_proj]->GetYaxis()->SetRangeUser(0.,0.9);
            h_contam[i_energy][i_proj]->SetMarkerStyle(marker_dca_style[0]);

            h_DCA_all[i_energy][i_proj]->SetMarkerColor(marker_res_color[0]);
            h_DCA_primary[i_energy][i_proj]->SetMarkerColor(marker_res_color[1]);
            h_DCA_secondary[i_energy][i_proj]->SetMarkerColor(marker_res_color[2]);

            h_contam[i_energy][i_proj]->SetMarkerColor(marker_res_color[i_proj]);
        }
    }

    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        h_n_hits_before[i_energy]->SetLineColor(marker_res_color[0]);
        h_n_hits_after[i_energy]->SetLineColor(marker_res_color[1]);

        h_mult[i_energy]->SetLineColor(marker_res_color[i_energy]);
        for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
            h_pt_reco_before[i_energy][i_sort]->SetLineColor(marker_res_color[0]);
            h_pt_reco_after[i_energy][i_sort]->SetLineColor(marker_res_color[1]);
            h_pt_true_before[i_energy][i_sort]->SetLineColor(marker_res_color[0]);
            h_pt_true_after[i_energy][i_sort]->SetLineColor(marker_res_color[1]);

            h_pt_reco_before[i_energy][i_sort]->SetMarkerStyle(marker_res_style[i_energy]);
            h_pt_reco_after[i_energy][i_sort]->SetMarkerStyle(marker_res_style[i_energy]);
            h_pt_true_before[i_energy][i_sort]->SetMarkerStyle(marker_res_style[i_energy]);
            h_pt_true_after[i_energy][i_sort]->SetMarkerStyle(marker_res_style[i_energy]);

            h_pt_reco_before[i_energy][i_sort]->SetLineStyle(line_pt_style[i_sort]);
            h_pt_reco_after[i_energy][i_sort]->SetLineStyle(line_pt_style[i_sort]);
            h_pt_true_before[i_energy][i_sort]->SetLineStyle(line_pt_style[i_sort]);
            h_pt_true_after[i_energy][i_sort]->SetLineStyle(line_pt_style[i_sort]);

            h_eta_reco_before[i_energy][i_sort]->SetLineColor(marker_res_color[0]);
            h_eta_reco_after[i_energy][i_sort]->SetLineColor(marker_res_color[1]);

            h_pt_eff_before[i_energy][i_sort]->SetLineColor(marker_res_color[i_energy]);
            h_pt_eff_after[i_energy][i_sort]->SetMarkerColor(marker_res_color[i_energy]);
            h_pt_eff_after[i_energy][i_sort]->SetMarkerStyle(marker_eff_style[i_energy]);

            h_pt_eff_after_HP[i_energy][i_sort]->SetMarkerColor(marker_eff_color[i_energy]);
            h_pt_eff_after_HP[i_energy][i_sort]->SetMarkerStyle(marker_eff_style[i_energy+2]);

            h_pt_eff_after_HP[i_energy][i_sort]->SetLineWidth(4);
            //h_pt_eff_after_HP[i_energy][i_sort]->SetLineStyle(2);
        }
    }

    for (Int_t i_harm=0; i_harm<n_harm; i_harm++){
        p_res_laqgsm_vs_centrality[i_harm]->SetXTitle("Centrality, %");
        h_res_laqgsm_vs_centrality[i_harm]->SetXTitle("Centrality, %");

        p_res_laqgsm_vs_centrality[i_harm]->SetMarkerStyle(marker_res_style[2]);
        h_res_laqgsm_vs_centrality[i_harm]->SetMarkerStyle(marker_res_style[3]);

        p_res_laqgsm_vs_centrality[i_harm]->SetMarkerColor(marker_res_color[3]);
        h_res_laqgsm_vs_centrality[i_harm]->SetMarkerColor(marker_res_color[3]);
    }

    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_harm=0; i_harm<n_harm;i_harm++){

            p_res_vs_centrality[i_energy][i_harm]->SetXTitle("Centrality, %");
            h_res_vs_centrality[i_energy][i_harm]->SetXTitle("Centrality, %");

            p_res_vs_centrality[i_energy][i_harm]->SetYTitle(Form("R_{%i} {#Psi_{EP,%i}}",i_harm+1,1));
            h_res_vs_centrality[i_energy][i_harm]->SetYTitle(Form("R_{%i} {#Psi_{EP,%i}}",i_harm+1,1));

            p_res_vs_centrality[i_energy][i_harm]->SetTitle("");
            h_res_vs_centrality[i_energy][i_harm]->SetTitle("");

            p_res_vs_centrality[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[0][i_energy]);
            h_res_vs_centrality[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[1][i_energy]);
            
            p_res_vs_centrality[i_energy][i_harm]->SetMarkerSize(1.);
            h_res_vs_centrality[i_energy][i_harm]->SetMarkerSize(1.1);

            p_res_vs_centrality[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);
            h_res_vs_centrality[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);

            p_vn_vs_centrality_true[i_energy][i_harm]->SetXTitle("Centrality, %");
            p_vn_vs_centrality_reco[i_energy][i_harm]->SetXTitle("Centrality, %");

            p_vn_vs_centrality_true[i_energy][i_harm]->SetYTitle(Form("v_{%i}",i_harm+1));
            p_vn_vs_centrality_reco[i_energy][i_harm]->SetYTitle(Form("v_{%i}",i_harm+1));

            p_vn_vs_centrality_true[i_energy][i_harm]->SetTitle("");
            p_vn_vs_centrality_reco[i_energy][i_harm]->SetTitle("");

            p_vn_vs_centrality_true[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[0][i_energy]);
            p_vn_vs_centrality_reco[i_energy][i_harm]->SetMarkerStyle(marker_flow_stl[1][i_energy]);

            p_vn_vs_centrality_true[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);
            p_vn_vs_centrality_reco[i_energy][i_harm]->SetMarkerColor(marker_res_color[i_energy]);

            for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
                for (Int_t i_sort=0;i_sort<n_sorts;i_sort++){

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->GetYaxis()->SetRangeUser(range_vn_pt[i_harm][0],range_vn_pt[i_harm][1] );
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->GetYaxis()->SetRangeUser(range_vn_rapidity[i_harm][0],range_vn_rapidity[i_harm][1] );
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->GetYaxis()->SetRangeUser(range_vn_pt[i_harm][0],range_vn_pt[i_harm][1] );
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->GetYaxis()->SetRangeUser(range_vn_rapidity[i_harm][0],range_vn_rapidity[i_harm][1] );

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetYTitle(Form("v_{%i}",i_harm+1));
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetYTitle(Form("v_{%i}",i_harm+1));
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetYTitle(Form("v_{%i}",i_harm+1));
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetYTitle(Form("v_{%i}",i_harm+1));

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetTitle("");
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetTitle("");
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetTitle("");
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetTitle("");

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetXTitle("p_{T}, GeV/c");
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetXTitle("y");
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetXTitle("p_{T}, GeV/c");
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetXTitle("y");

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetMarkerStyle(marker_flow_stl[1][i_sort]);
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetMarkerStyle(marker_flow_stl[1][i_sort]);
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetMarkerStyle(marker_flow_stl[0][i_sort]);
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetMarkerStyle(marker_flow_stl[0][i_sort]);
                    
                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetMarkerSize(1.1);
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetMarkerSize(1.1);

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetMarkerColor(marker_res_color[i_sort]);
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetMarkerColor(marker_res_color[i_sort]);
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetMarkerColor(marker_res_color[i_sort]);
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetMarkerColor(marker_res_color[i_sort]);

                    p_vn_reco_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetLineColor(marker_res_color[i_sort]);
                    p_vn_reco_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetLineColor(marker_res_color[i_sort]);
                    p_vn_true_vs_pt[i_energy][i_harm][i_cent][i_sort]       ->SetLineColor(marker_res_color[i_sort]);
                    p_vn_true_vs_rapidity[i_energy][i_harm][i_cent][i_sort] ->SetLineColor(marker_res_color[i_sort]);
                }
            }
        }
    }

    TLatex* text = new TLatex();
    text->SetTextSize(0.04);
    text->SetTextAlign(13);

    //MULTIPLICITY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_mult = new TCanvas("c_mult","Multiplicity",500,500);
    TLegend* leg_mult = new TLegend(0.25,0.75,0.95,0.95);
    c_mult->cd();
    c_mult->SetLogy();
    h_mult[0]->GetXaxis()->SetRangeUser(mult_range[0],mult_range[1]);
    h_mult[0]->GetXaxis()->SetNdivisions(5);
    h_mult[0]->SetTitle("");
    h_mult[0]->Draw("");
    //h_mult[1]->Draw("SAME");
    leg_mult->SetHeader("Au-Au #sqrt{s_{NN}} = 11 GeV, UrQMD, GEANT3, 2M events","C");
    leg_mult->AddEntry(h_mult[0],energy_title[0].Data(),"l");
    //leg_mult->AddEntry(h_mult[1],energy_title[1].Data(),"l");
    leg_mult->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

    c_mult->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/multiplicity.eps","recreate");
    c_mult->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/multiplicity.png","recreate");
    c_mult->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/multiplicity.pdf","recreate");
    c_mult->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/multiplicity.C","recreate");

    //SIGMA B/B VS CENTRALITY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_b_cent = new TCanvas("c_b_cent","sigma b",500,500);
    TLegend* leg_sigm = new TLegend(0.25,0.75,0.95,0.95);
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (int bin = 1; bin < h2_b_vs_centrality[i_energy]->GetNbinsX(); ++bin){
            if ( h2_b_vs_centrality[i_energy]->ProjectionY("",bin,bin)->GetRMS() != 0)
                p_resolution_vs_centrality[i_energy]->Fill(bin,h2_b_vs_centrality[i_energy]->ProjectionY("",bin,bin)->GetRMS()/h2_b_vs_centrality[i_energy]->ProjectionY("",bin,bin)->GetMean());
        }
    }
    c_b_cent->cd();
    p_resolution_vs_centrality[0]->Draw("P");
    //p_resolution_vs_centrality[1]->Draw("P,SAME");
    leg_sigm->SetHeader("Au-Au #sqrt{s_{NN}} = 11 GeV, UrQMD, GEANT3, 2M events","C");
    leg_sigm->AddEntry(p_resolution_vs_centrality[0],energy_title[0].Data(),"p");
    //leg_sigm->AddEntry(p_resolution_vs_centrality[1],energy_title[1].Data(),"p");
    leg_sigm->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

    c_b_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/b_vs_mult.eps","recreate");
    c_b_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/b_vs_mult.png","recreate");
    c_b_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/b_vs_mult.pdf","recreate");
    c_b_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/b_vs_mult.C","recreate");

    //EFFICIENCY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_eff   = new TCanvas("c_eff","Efficiency",500,500);
    TLegend* leg_eff = new TLegend(0.35,0.24,0.79,0.55);
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
            for (Int_t i_cent=0;i_cent<n_centrality;i_cent++){
                h_pt_reco_before[i_energy][i_sort]->Add(h_pt_reco_in_before[i_energy][i_cent][i_sort]);
                h_pt_true_before[i_energy][i_sort]->Add(h_pt_true_in_before[i_energy][i_cent][i_sort]);
                h_pt_reco_after[i_energy][i_sort]->Add(h_pt_reco_in_after[i_energy][i_cent][i_sort]);
                h_pt_true_after[i_energy][i_sort]->Add(h_pt_true_in_after[i_energy][i_cent][i_sort]);

                //h_pt_reco_after_HP[i_energy][i_sort]->Add(h_pt_reco_in_after_HP[i_energy][i_cent][i_sort]);
                //h_pt_true_after_HP[i_energy][i_sort]->Add(h_pt_true_in_after_HP[i_energy][i_cent][i_sort]);

                if (i_cent==1) h_eta_reco_before[i_energy][i_sort]->Add(h_eta_reco_in_before[i_energy][i_cent][i_sort]);
                if (i_cent==1) h_eta_reco_after[i_energy][i_sort]->Add(h_eta_reco_in_after[i_energy][i_cent][i_sort]);
            }
        }
    }
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_sort=0;i_sort<n_sorts+1;i_sort++){
            h_pt_eff_before[i_energy][i_sort]->Divide(h_pt_reco_before[i_energy][i_sort],h_pt_true_before[i_energy][i_sort]);
            h_pt_eff_after[i_energy][i_sort]->Divide(h_pt_reco_after[i_energy][i_sort],h_pt_true_after[i_energy][i_sort]);

            //h_pt_eff_after_HP[i_energy][i_sort]->Divide(h_pt_reco_after_HP[i_energy][i_sort],h_pt_true_after_HP[i_energy][i_sort]);
        }
    }
    c_eff->cd();
    h_pt_eff_after[0][2]->GetXaxis()->SetRangeUser(0,2.);
    h_pt_eff_after[0][2]->GetXaxis()->SetNdivisions(5);
    h_pt_eff_after[0][2]->SetMarkerStyle(marker_flow_stl[0][1]);
    h_pt_eff_after[0][1]->SetMarkerStyle(marker_flow_stl[0][0]);
    h_pt_eff_after[0][3]->SetMarkerStyle(marker_flow_stl[0][2]);
    h_pt_eff_after[0][2]->SetMarkerColor(marker_res_color[1]);
    h_pt_eff_after[0][1]->SetMarkerColor(marker_res_color[0]);
    h_pt_eff_after[0][3]->SetMarkerColor(marker_res_color[2]);
    //h_pt_true_after[0][2]->Draw("");
    //h_pt_reco_after[0][2]->Draw("SAME");
    h_pt_eff_after[0][2]->Draw("P");
    h_pt_eff_after[0][1]->Draw("PSAME");
    h_pt_eff_after[0][3]->Draw("PSAME");
    //h_pt_eff_after[1][2]->Draw("P,SAME");
    //h_pt_eff_after_HP[0][2]->Draw("P,SAME");
    //h_pt_eff_after_HP[1][2]->Draw("P,SAME");
    leg_eff->AddEntry(h_pt_eff_after[0][2],Form("Protons"),"p");
    leg_eff->AddEntry(h_pt_eff_after[0][1],Form("Pions"),"p");
    leg_eff->AddEntry(h_pt_eff_after[0][3],Form("Kaons"),"p");
    //leg_eff->AddEntry(h_pt_eff_after_HP[0][2],Form("motherID,  HITS"),"p");
    //leg_eff->AddEntry(h_pt_eff_after[1][2],Form("2#sigma DCA, CLUSTERS"),"p");
    //leg_eff->AddEntry(h_pt_eff_after_HP[1][2],Form("motherID, CLUSTERS"),"p");
    leg_eff->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

    c_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Efficiency.eps","recreate");
    c_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Efficiency.png","recreate");
    c_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Efficiency.pdf","recreate");
    c_eff->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/Efficiency.C","recreate");

    //TRACK SELECTION
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_track_selection = new TCanvas("c_track_selection","track selection",1000,1000);
    TLegend* leg_sel = new TLegend(0.48,0.71,0.87,0.89);
    TLegend* leg_pid = new TLegend(0.68,0.63,0.87,0.82);
    c_track_selection->Divide(2,2);
    c_track_selection->cd(1);
    c_track_selection->cd(1)->SetLogy();
    h_pt_reco_before[0][0]->GetXaxis()->SetRangeUser(pt_track_range[0],pt_track_range[1]);
    h_pt_reco_before[0][0]->Draw();
    h_pt_reco_after[0][0]->Draw("SAME");
    leg_sel->AddEntry((TObject*)0,Form("UrQMD Au+Au, %s",energy_title[0].Data()),"");
    leg_sel->AddEntry(h_pt_reco_before[0][0],"no cut","l");
    leg_sel->AddEntry(h_pt_reco_after[0][0],"with cut","l");
    leg_sel->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_track_selection->cd(2);
    c_track_selection->cd(2)->SetLogy();
    h_eta_reco_before[0][0]->GetXaxis()->SetRangeUser(eta_track_range[0],eta_track_range[1]);
    h_eta_reco_before[0][0]->Draw();
    h_eta_reco_after[0][0]->Draw("SAME");
    //leg_sel->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_track_selection->cd(3);
    c_track_selection->cd(3)->SetLogy();
    h_n_hits_before[0]->GetXaxis()->SetRangeUser(n_hits_range[0],n_hits_range[1]);
    h_n_hits_before[0]->Draw("");
    h_n_hits_after[0]->Draw("SAME");
    //leg_sel->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_track_selection->cd(4);
    c_track_selection->cd(4)->SetLogy();
    h_pt_reco_before[0][1]->GetXaxis()->SetRangeUser(pt_track_range[0],pt_track_range[1]);
    h_pt_reco_before[0][1]->Draw();
    h_pt_reco_after[0][1]->Draw("SAME");
    h_pt_reco_before[0][2]->Draw("SAME");
    h_pt_reco_after[0][2]->Draw("SAME");
    h_pt_reco_before[0][3]->Draw("SAME");
    h_pt_reco_after[0][3]->Draw("SAME");
    leg_pid->AddEntry(h_pt_reco_before[0][1],"#pi","l");
    leg_pid->AddEntry(h_pt_reco_before[0][2],"p","l");
    leg_pid->AddEntry(h_pt_reco_before[0][3],"K","l");
    //leg_sel->Draw();
    leg_pid->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

    c_track_selection->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/track_selection.eps","recreate");
    c_track_selection->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/track_selection.png","recreate");
    c_track_selection->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/track_selection.pdf","recreate");
    c_track_selection->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/track_selection.C","recreate");

    //DCA
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_dca = new TCanvas("c_dca","dca",700,700);
    TLegend* leg_dca    = new TLegend(0.68,0.71,0.87,0.89);
    TLegend* leg_contam = new TLegend(0.68,0.23,0.87,0.42);
    c_dca->Divide(2,2);
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_proj=0;i_proj<n_proj;i_proj++){
            for (Int_t i_pt=0;i_pt<NptBins;i_pt++){
                for (Int_t i_eta=0;i_eta<NetaBins;i_eta++){
                    h_DCA_all[i_energy][i_proj]->Add(h_DCA_in_all[i_energy][i_proj][i_pt][i_eta]);
                    h_DCA_primary[i_energy][i_proj]->Add(h_DCA_in_primary[i_energy][i_proj][i_pt][i_eta]);
                    h_DCA_secondary[i_energy][i_proj]->Add(h_DCA_in_secondary[i_energy][i_proj][i_pt][i_eta]);
                }
            }
        }
    }

    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_proj=0;i_proj<n_proj;i_proj++){
            h_contam[i_energy][i_proj]->Divide(h_DCA_secondary[i_energy][i_proj],h_DCA_all[i_energy][i_proj]);
        }
    }
    c_dca->cd(1);
    c_dca->cd(1)->SetLogy();
    h_DCA_all[0][0]->GetXaxis()->SetRangeUser(dca_x_range[0],dca_x_range[1]);
    h_DCA_all[0][0]->GetYaxis()->SetRangeUser(range_dca[0],range_dca[1]);
    h_DCA_all[0][0]->Draw();
    h_DCA_primary[0][0]->Draw("SAME");
    h_DCA_secondary[0][0]->Draw("SAME");
    leg_dca->AddEntry(h_DCA_all[0][0],"All","p");
    leg_dca->AddEntry(h_DCA_primary[0][0],"Primary","p");
    leg_dca->AddEntry(h_DCA_secondary[0][0],"Secondary","p");
    leg_dca->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_dca->cd(2);
    c_dca->cd(2)->SetLogy();
    h_DCA_all[0][1]->GetXaxis()->SetRangeUser(dca_x_range[0],dca_x_range[1]);
    h_DCA_all[0][1]->GetYaxis()->SetRangeUser(range_dca[0],range_dca[1]);
    h_DCA_all[0][1]->Draw();
    h_DCA_primary[0][1]->Draw("SAME");
    h_DCA_secondary[0][1]->Draw("SAME");
    leg_dca->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_dca->cd(3);
    c_dca->cd(3)->SetLogy();
    h_DCA_all[0][2]->GetXaxis()->SetRangeUser(dca_x_range[0],dca_x_range[1]);
    h_DCA_all[0][2]->GetYaxis()->SetRangeUser(range_dca[0],range_dca[1]);
    h_DCA_all[0][2]->Draw();
    h_DCA_primary[0][2]->Draw("SAME");
    h_DCA_secondary[0][2]->Draw("SAME");
    leg_dca->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    c_dca->cd(4);
    h_contam[0][0]->GetXaxis()->SetRangeUser(dca_x_range[0],dca_x_range[1]);
    h_contam[0][0]->Draw();
    h_contam[0][1]->Draw("SAME");
    h_contam[0][2]->Draw("SAME");
    leg_contam->AddEntry(h_contam[0][0],"DCA_{x}","p");
    leg_contam->AddEntry(h_contam[0][1],"DCA_{y}","p");
    leg_contam->AddEntry(h_contam[0][2],"DCA_{z}","p");
    leg_contam->Draw();
    //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

    c_dca->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/dca.eps","recreate");
    c_dca->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/dca.png","recreate");
    c_dca->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/dca.pdf","recreate");
    c_dca->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/dca.C","recreate");

    //RESOLUTION VS CENTRALITY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_res   = new TCanvas("c_res","Resolution",1000,500);
    TLegend* leg_res;
    TLegend* leg_res_energy;

    leg_res = new TLegend(0.23,0.75,0.85,0.88);

    leg_res_energy = new TLegend(0.65,0.75,0.85,0.88);

    c_res->Divide(2,1);

    leg_res->SetHeader("Au-Au, #sqrt{s_{NN}}=11 GeV, GEANT3","C");
    leg_res->SetNColumns(2);
    //leg_res->AddEntry((TObject*)0,"","");
    //leg_res->AddEntry((TObject*)0,"","");
    TLegendEntry *headerRes = (TLegendEntry*)leg_res->GetListOfPrimitives()->First();
    headerRes->SetTextSize(.033);
    //leg_res->AddEntry((TObject*)0,"UrQMD Au+Au","");
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        leg_res->AddEntry(h_res_vs_centrality[i_energy][0],("UrQMD"),"p");
    }
    leg_res->AddEntry(p_res_vs_centrality[0][0],"true","p");
    //leg_res->AddEntry((TObject*)0,"LAQGSM Au+Au","");
    leg_res->AddEntry(p_res_laqgsm_vs_centrality[0],("LAQGSM"),"p");
    leg_res->AddEntry(h_res_vs_centrality[0][0],"reco","p");
    //leg_res_energy->SetHeader("Au-Au, 11 GeV");
    leg_res_energy->AddEntry(p_res_vs_centrality[0][0],"true","p");
    leg_res_energy->GetEntry()->SetTextSize(.035);
    leg_res_energy->AddEntry(h_res_vs_centrality[0][0],"reco","p");
    leg_res_energy->GetEntry()->SetTextSize(.035);
    TLegendEntry *headerRes1 = (TLegendEntry*)leg_res_energy->GetListOfPrimitives()->First();
    headerRes1->SetTextSize(.035);

    for (Int_t i=0;i<2;i++){
        c_res->cd(i+1);
        p_res_vs_centrality[0][i]->GetYaxis()->SetRangeUser(res_range[i][0],res_range[i][1]);
        p_res_vs_centrality[0][i]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        p_res_vs_centrality[0][i]->GetYaxis()->SetNdivisions(5);
        p_res_vs_centrality[0][i]       ->SetMarkerSize(1.4);
        h_res_vs_centrality[0][i]       ->SetMarkerSize(1.4);
        p_res_laqgsm_vs_centrality[i]   ->SetMarkerSize(1.4);
        h_res_laqgsm_vs_centrality[i]   ->SetMarkerSize(1.4);
        p_res_vs_centrality[0][i]->Draw();
        h_res_vs_centrality[0][i]->Draw("PSAME,HIST");
        //p_res_vs_centrality[1][i]->Draw("SAME");
        //h_res_vs_centrality[1][i]->Draw("PSAME,HIST");
        p_res_laqgsm_vs_centrality[i]->Draw("PHISTSAME");
        h_res_laqgsm_vs_centrality[i]->Draw("PHISTSAME");
        leg_res->Draw();
        //leg_res_energy->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    }
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/res_vs_centrality.eps","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/res_vs_centrality.png","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/res_vs_centrality.pdf","recreate");
    c_res->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/res_vs_centrality.C","recreate");
    
    //VN VS CENTRALITY
    //--------------------------------------------------------------------------------------------------------
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        for (Int_t i_harm=0;i_harm<n_harm;i_harm++){
            for (Int_t i_sort=0;i_sort<n_sorts;i_sort++){
                p_vn_vs_centrality_true[i_energy][i_harm]->Add(p_vn_vs_centrality[i_energy][i_harm][i_sort]);
                p_vn_vs_centrality_reco[i_energy][i_harm]->Add(h_vn_vs_centrality[i_energy][i_harm][i_sort]);
            }
        }
    }

    TCanvas* c_vn_cent   = new TCanvas("c_vn_cent","v_{n} vs centrality",1000,500);
    TLegend* leg_cv_cent;
    TLegend* leg_cv_cent_energy;

    leg_cv_cent = new TLegend(0.33,0.24,0.50,0.41);

    leg_cv_cent_energy = new TLegend(0.66,0.69,0.85,0.87);

    c_vn_cent->Divide(2,1);

    leg_cv_cent->AddEntry((TObject*)0,"UrQMD Au+Au","");
    for (Int_t i_energy=0;i_energy<n_energy;i_energy++){
        leg_cv_cent->AddEntry(p_vn_vs_centrality_reco[i_energy][0],energy_title[i_energy].Data(),"p");
    }
    leg_cv_cent_energy->SetHeader("FHCal");
    leg_cv_cent_energy->AddEntry(p_vn_vs_centrality_true[0][0],"true","p");
    leg_cv_cent_energy->AddEntry(p_vn_vs_centrality_reco[0][0],"reco","p");

    for (Int_t i=0;i<2;i++){
        c_vn_cent->cd(i+1);
        p_vn_vs_centrality_true[0][i]->GetYaxis()->SetRangeUser(vn_cent_range[i][0],vn_cent_range[i][1]);
        p_vn_vs_centrality_true[0][i]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        p_vn_vs_centrality_true[0][i]->Draw();
        p_vn_vs_centrality_reco[0][i]->Draw("PSAME,HIST");
        //p_vn_vs_centrality_true[1][i]->Draw("SAME");
        //p_vn_vs_centrality_reco[1][i]->Draw("PSAME,HIST");
        //p_vn_vs_centrality[0][i][2]->GetYaxis()->SetRangeUser(vn_cent_range[i][0],vn_cent_range[i][1]);
        //p_vn_vs_centrality[0][i][2]->GetXaxis()->SetRangeUser(centrality_range[0],centrality_range[1]);
        //p_vn_vs_centrality[0][i][2]->Draw();
        //h_vn_vs_centrality[0][i][2]->Draw("PSAME,HIST");
        //p_vn_vs_centrality[1][i][2]->Draw("SAME");
        //p_vn_vs_centrality_reco[1][i]->Draw("PSAME,HIST");
        leg_cv_cent_energy->Draw();
        leg_cv_cent->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
    }
    c_vn_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_centrality.eps","recreate");
    c_vn_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_centrality.png","recreate");
    c_vn_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_centrality.pdf","recreate");
    c_vn_cent->SaveAs("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_centrality.C","recreate");

    //VN VS PT
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_vn_pt[n_energy];
    TLegend* leg_vn_pt[n_energy][4];
    TLegend* leg_vn_type[n_energy][4];
    TLegendEntry *headerPt;
    TLine*   line = new TLine();
    line->SetLineStyle(2);
    line->SetLineWidth(2);

    for (Int_t i_energy=0; i_energy<n_energy; i_energy++){
        for (Int_t i=0;i<4;i++){
            leg_vn_pt[i_energy][i] = new TLegend(0.2,0.65,0.89,0.89);
            leg_vn_type[i_energy][i] = new TLegend(0.58,0.25,0.88,0.35);
        }
    }

    for (Int_t i_energy=0; i_energy<n_energy;i_energy++){

        c_vn_pt[i_energy] = new TCanvas(Form("c_vn_pt%i",i_energy),Form("vn vs pt %i", i_energy),700,700);
        c_vn_pt[i_energy]-> Divide(2,2);
        c_vn_pt[i_energy]->cd(1);
        leg_vn_pt[i_energy][0]->SetHeader(vn_Title[0].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][0]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][0]->SetNColumns(2);
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"true"     ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"reco"     ,"p");
        leg_vn_pt[i_energy][0]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][0]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][0][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][0][0][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_pt[i_energy][0][0][0]->Draw();
        leg_vn_pt[i_energy][0]->Draw();
        p_vn_reco_vs_pt[i_energy][0][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][0][2]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][0][0]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][0][1]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][0][2]->Draw("SAME");
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
        c_vn_pt[i_energy]->cd(2);
        leg_vn_pt[i_energy][1]->SetHeader(vn_Title[1].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][1]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][1]->SetNColumns(2);
        leg_vn_pt[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][1]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"true"     ,"p");
        leg_vn_pt[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"reco"     ,"p");
        leg_vn_pt[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][1]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][0][1][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][0][1][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_pt[i_energy][0][1][0]->Draw();
        leg_vn_pt[i_energy][1]->Draw();
        p_vn_reco_vs_pt[i_energy][0][1][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][1][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][0][1][2]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][1][0]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][1][1]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][0][1][2]->Draw("SAME");
        line->DrawLine(pt_range[0],0.,pt_range[1],0.);
        leg_vn_type[i_energy][1]->SetHeader("20-40%");
        leg_vn_type[i_energy][1]->SetNColumns(3);
        leg_vn_type[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][1][0]," p"        ,"p");
        leg_vn_type[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][1][1]," K^{+}"    ,"p");
        leg_vn_type[i_energy][1]->AddEntry(p_vn_reco_vs_pt[i_energy][0][1][2]," #pi^{+}"  ,"p");
        //headerPt = (TLegendEntry*)leg_vn_type[i_energy][1]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_pt[i_energy]->SetHeader(Form("Au-Au, #sqrt{s_{NN}}=11 GeV, 20-40%, GEANT3, UrQMD, 4M events","C"));
        //leg_vn_type[i_energy][1]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        c_vn_pt[i_energy]->cd(3);
        leg_vn_pt[i_energy][2]->SetHeader(vn_Title[0].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][2]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][2]->SetNColumns(2);
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"true"     ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"reco"     ,"p");
        leg_vn_pt[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][2]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][1][0][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][1][0][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_pt[i_energy][1][0][0]->Draw();
        leg_vn_pt[i_energy][2]->Draw();
        p_vn_reco_vs_pt[i_energy][1][0][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][0][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][0][2]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][0][0]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][0][1]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][0][2]->Draw("SAME");
        leg_vn_type[i_energy][2]->SetHeader("10-20%");
        leg_vn_type[i_energy][2]->SetNColumns(3);
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][0]," p"        ,"p");
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][1]," K^{+}"    ,"p");
        leg_vn_type[i_energy][2]->AddEntry(p_vn_reco_vs_pt[i_energy][1][0][2]," #pi^{+}"  ,"p");
        //headerPt = (TLegendEntry*)leg_vn_type[i_energy][2]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_type[i_energy][2]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        c_vn_pt[i_energy]->cd(4);
        leg_vn_pt[i_energy][3]->SetHeader(vn_Title[1].Data(),"C");
        headerPt = (TLegendEntry*)leg_vn_pt[i_energy][3]->GetListOfPrimitives()->First();
        headerPt->SetTextSize(.028);
        leg_vn_pt[i_energy][3]->SetNColumns(2);
        leg_vn_pt[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"PROTON (p)"       ,"p");
        leg_vn_pt[i_energy][3]->AddEntry(p_vn_true_vs_pt[i_energy][0][0][0],"true"     ,"p");
        leg_vn_pt[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][1],"KAON (K^{+})"   ,"p");
        leg_vn_pt[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][0],"reco"     ,"p");
        leg_vn_pt[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][0][0][2],"PION (#pi^{+})" ,"p");
        leg_vn_pt[i_energy][3]->AddEntry((TObject*)0,"","");
        p_vn_reco_vs_pt[i_energy][1][1][0]->GetXaxis()->SetRangeUser(pt_range[0],pt_range[1]);
        p_vn_reco_vs_pt[i_energy][1][1][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_pt[i_energy][1][1][0]->Draw();
        leg_vn_pt[i_energy][3]->Draw();
        p_vn_reco_vs_pt[i_energy][1][1][0]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][1][1]->Draw("SAME");
        p_vn_reco_vs_pt[i_energy][1][1][2]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][1][0]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][1][1]->Draw("SAME");
        p_vn_true_vs_pt[i_energy][1][1][2]->Draw("SAME");
        leg_vn_type[i_energy][3]->SetHeader("20-40%");
        leg_vn_type[i_energy][3]->SetNColumns(3);
        leg_vn_type[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][1][1][0]," p"        ,"p");
        leg_vn_type[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][1][1][1]," K^{+}"    ,"p");
        leg_vn_type[i_energy][3]->AddEntry(p_vn_reco_vs_pt[i_energy][1][1][2]," #pi^{+}"  ,"p");
        //headerPt = (TLegendEntry*)leg_vn_type[i_energy][3]->GetListOfPrimitives()->First();
        //headerPt->SetTextSize(.035);
        //leg_vn_type[i_energy][3]->Draw();
        //text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_pt_%i.eps",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_pt_%i.png",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_pt_%i.pdf",i_energy),"recreate");
        c_vn_pt[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_pt_%i.C",i_energy),"recreate");
    }

    //VN VS RAPIDITY
    //--------------------------------------------------------------------------------------------------------
    TCanvas* c_vn_rapidity[n_energy];
    TCanvas* c_vn_mc_y[n_energy];
    TLegend* leg_vn_rapidity[n_energy];
    TLegend* leg_vn_type_rapidity[n_energy][4];
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    TLatex* mc_vn_text = new TLatex();
    mc_vn_text->SetTextSize(0.04);
    mc_vn_text->SetTextAlign(13);

    for (Int_t i_energy=0; i_energy<n_energy; i_energy++){
    leg_vn_rapidity[i_energy] = new TLegend(0.22,0.68,0.48,0.86);
        for (Int_t i=0;i<4;i++){
            leg_vn_type_rapidity[i_energy][i] = new TLegend(0.38,0.6,0.67,0.82);
        }
    }

    for (Int_t i_energy=0; i_energy<n_energy;i_energy++){

        c_vn_rapidity[i_energy] = new TCanvas(Form("c_vn_rapidity%i",i_energy),Form("vn vs y %i", i_energy),700,700);
        c_vn_rapidity[i_energy]-> Divide(2,2);
        c_vn_rapidity[i_energy]->cd(1);
        leg_vn_rapidity[i_energy]->SetHeader(Form("%s",energy_title[i_energy].Data()));
        leg_vn_rapidity[i_energy]->AddEntry(p_vn_true_vs_rapidity[i_energy][0][0][0],"true","p");
        leg_vn_rapidity[i_energy]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][0][0],"reco","p");
        p_vn_reco_vs_rapidity[i_energy][0][0][0]->GetXaxis()->SetRangeUser(rapidity_range[0],rapidity_range[1]);
        p_vn_reco_vs_rapidity[i_energy][0][0][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_rapidity[i_energy][0][0][0]->Draw();
        p_vn_reco_vs_rapidity[i_energy][0][0][1]->Draw("SAME");
        p_vn_reco_vs_rapidity[i_energy][0][0][2]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][0][0]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][0][1]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][0][2]->Draw("SAME");
        leg_vn_type_rapidity[i_energy][0]->SetHeader("10-20%");
        leg_vn_type_rapidity[i_energy][0]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][0][0],"p, (TOF+TPC) PID"        ,"p");
        leg_vn_type_rapidity[i_energy][0]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][0][1],"K^{+}, (TOF+TPC) PID"    ,"p");
        leg_vn_type_rapidity[i_energy][0]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][0][2],"#pi^{+}, (TOF+TPC) PID"  ,"p");
        TLegendEntry *headerEta = (TLegendEntry*)leg_vn_type_rapidity[i_energy][0]->GetListOfPrimitives()->First();
        headerEta->SetTextSize(.035);
        leg_vn_rapidity[i_energy]->Draw();
        leg_vn_type_rapidity[i_energy][0]->Draw();
        text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        line->DrawLine(rapidity_range[0],0.,rapidity_range[1],0.);
        c_vn_rapidity[i_energy]->cd(2);
        p_vn_reco_vs_rapidity[i_energy][0][1][0]->GetXaxis()->SetRangeUser(rapidity_range[0],rapidity_range[1]);
        p_vn_reco_vs_rapidity[i_energy][0][1][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_rapidity[i_energy][0][1][0]->Draw();
        p_vn_reco_vs_rapidity[i_energy][0][1][1]->Draw("SAME");
        p_vn_reco_vs_rapidity[i_energy][0][1][2]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][1][0]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][1][1]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][1][2]->Draw("SAME");
        leg_vn_type_rapidity[i_energy][1]->SetHeader("20-40%");
        leg_vn_type_rapidity[i_energy][1]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][1][0],"p, (TOF+TPC) PID"        ,"p");
        leg_vn_type_rapidity[i_energy][1]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][1][1],"K^{+}, (TOF+TPC) PID"    ,"p");
        leg_vn_type_rapidity[i_energy][1]->AddEntry(p_vn_reco_vs_rapidity[i_energy][0][1][2],"#pi^{+}, (TOF+TPC) PID"  ,"p");
        headerEta = (TLegendEntry*)leg_vn_type_rapidity[i_energy][1]->GetListOfPrimitives()->First();
        headerEta->SetTextSize(.035);
        leg_vn_rapidity[i_energy]->Draw();
        leg_vn_type_rapidity[i_energy][1]->Draw();
        text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        line->DrawLine(rapidity_range[0],0.,rapidity_range[1],0.);
        c_vn_rapidity[i_energy]->cd(3);
        p_vn_reco_vs_rapidity[i_energy][1][0][0]->GetXaxis()->SetRangeUser(rapidity_range[0],rapidity_range[1]);
        p_vn_reco_vs_rapidity[i_energy][1][0][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_rapidity[i_energy][1][0][0]->Draw();
        p_vn_reco_vs_rapidity[i_energy][1][0][1]->Draw("SAME");
        p_vn_reco_vs_rapidity[i_energy][1][0][2]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][0][0]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][0][1]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][0][2]->Draw("SAME");
        leg_vn_type_rapidity[i_energy][2]->SetHeader("10-20%");
        leg_vn_type_rapidity[i_energy][2]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][0][0],"p, (TOF+TPC) PID"        ,"p");
        leg_vn_type_rapidity[i_energy][2]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][0][1],"K^{+}, (TOF+TPC) PID"    ,"p");
        leg_vn_type_rapidity[i_energy][2]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][0][2],"#pi^{+}, (TOF+TPC) PID"  ,"p");
        headerEta = (TLegendEntry*)leg_vn_type_rapidity[i_energy][2]->GetListOfPrimitives()->First();
        headerEta->SetTextSize(.035);
        leg_vn_rapidity[i_energy]->Draw();
        leg_vn_type_rapidity[i_energy][2]->Draw();
        text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);
        c_vn_rapidity[i_energy]->cd(4);
        p_vn_reco_vs_rapidity[i_energy][1][1][0]->GetXaxis()->SetRangeUser(rapidity_range[0],rapidity_range[1]);
        p_vn_reco_vs_rapidity[i_energy][1][1][0]->GetXaxis()->SetNdivisions(5);
        p_vn_reco_vs_rapidity[i_energy][1][1][0]->Draw();
        p_vn_reco_vs_rapidity[i_energy][1][1][1]->Draw("SAME");
        p_vn_reco_vs_rapidity[i_energy][1][1][2]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][1][0]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][1][1]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][1][1][2]->Draw("SAME");
        leg_vn_type_rapidity[i_energy][3]->SetHeader("20-40%");
        leg_vn_type_rapidity[i_energy][3]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][1][0],"p, (TOF+TPC) PID"        ,"p");
        leg_vn_type_rapidity[i_energy][3]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][1][1],"K^{+}, (TOF+TPC) PID"    ,"p");
        leg_vn_type_rapidity[i_energy][3]->AddEntry(p_vn_reco_vs_rapidity[i_energy][1][1][2],"#pi^{+}, (TOF+TPC) PID"  ,"p");
        headerEta = (TLegendEntry*)leg_vn_type_rapidity[i_energy][3]->GetListOfPrimitives()->First();
        headerEta->SetTextSize(.035);
        leg_vn_rapidity[i_energy]->Draw();
        leg_vn_type_rapidity[i_energy][3]->Draw();
        text->DrawLatexNDC(latex_coord[0],latex_coord[1],latex_title);

        c_vn_mc_y[i_energy] = new TCanvas(Form("c_vn_mc_y%i",i_energy),Form("vn vs y mc %i",i_energy),500,500);
        c_vn_mc_y[i_energy]->cd();
        p_vn_true_vs_rapidity[i_energy][0][0][0]->GetXaxis()->SetRangeUser(rapidity_range[0],rapidity_range[1]);
        p_vn_reco_vs_rapidity[i_energy][0][0][0]->GetXaxis()->SetNdivisions(5);
        p_vn_true_vs_rapidity[i_energy][0][0][0]->Draw("");
        p_vn_true_vs_rapidity[i_energy][0][0][1]->Draw("SAME");
        p_vn_true_vs_rapidity[i_energy][0][0][2]->Draw("SAME");
        line->DrawLine(rapidity_range[0],0.,rapidity_range[1],0.);
        if (i_energy==0) mc_vn_text->DrawLatexNDC(0.8,0.81,"p");
        //if (i_energy==1) mc_vn_text->DrawLatexNDC(0.8,0.72,"p");
        if (i_energy==0) mc_vn_text->DrawLatexNDC(0.3,0.85,"Au+Au 5 GeV");
        //if (i_energy==1) mc_vn_text->DrawLatexNDC(0.3,0.85,"Au+Au 11 GeV");
        mc_vn_text->DrawLatexNDC(0.3,0.81,"UrQMD");
        if (i_energy==0) mc_vn_text->DrawLatexNDC(0.8,0.42,"#color[4]{#bf{#pi}}");
        //if (i_energy==1) mc_vn_text->DrawLatexNDC(0.8,0.49,"#color[4]{#bf{#pi}}");

        c_vn_rapidity[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_rapidity_%i.eps",i_energy),"recreate");
        c_vn_rapidity[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_rapidity_%i.png",i_energy),"recreate");
        c_vn_rapidity[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_rapidity_%i.pdf",i_energy),"recreate");
        c_vn_rapidity[i_energy]->SaveAs(Form("/home/peter/Documents/WorkLocal/MPD/Pics/Final1/vn_vs_rapidity_%i.C",i_energy),"recreate");
    }
//*/
}
