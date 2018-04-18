//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 22 16:16:04 2018 by ROOT version 6.13/01
// from TTree cbmsim_reduced/cbmsim_reduced
// found on file: merged_0_clone.root
//////////////////////////////////////////////////////////

#ifndef PicoDstPidReader_h
#define PicoDstPidReader_h

#ifndef _MAX_TRACKS
#define _MAX_TRACKS 200000
#endif

#include <iostream>
#include <stdio.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "BinningData.cxx"

const float ptBins[] = {0.,0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.5, 3.};
const int   NptBins = 12;

const float rapidityBins[] = {-2., -1.8, -1.6, -1.4,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.};
const int   NrapidityBins = 20;

const float etaBins[] = {-1.5,-1.,-0.5,0.,0.5,1.,1.5};
const int   NetaBins = 6;
//const float etaBins[] = {-1.5,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1.,1.2,1.5};
//const int   NetaBins = 14;

const int   Npid = 4;
TString     s_pid[Npid] = {TString("All"), TString("Pions"), TString("Kaons"), TString("Protons")};

struct InputTH1Info{
   TString  name;
   TString  title;
   Int_t    Nbins;
   Double_t Xmin;
   Double_t Xmax;
};

struct InputTH2Info{
   TString  name;
   TString  title;
   Int_t    NbinsX;
   Int_t    NbinsY;
   Double_t Xmin;
   Double_t Xmax;
   Double_t Ymin;
   Double_t Ymax;
};

TH1F* InitTH1F(InputTH1Info inf)
{
   return new TH1F(inf.name, inf.title, inf.Nbins, inf.Xmin, inf.Xmax);
}

TH1F* InitTH1F(InputTH1Info * inf)
{
   return new TH1F(inf->name, inf->title, inf->Nbins, inf->Xmin, inf->Xmax);
}

TH2F* InitTH2F(InputTH2Info inf)
{
   return new TH2F(inf.name, inf.title, inf.NbinsX, inf.Xmin, inf.Xmax, inf.NbinsY, inf.Ymin, inf.Ymax);
}

TH2F* InitTH2F(InputTH2Info * inf)
{
   return new TH2F(inf->name, inf->title, inf->NbinsX, inf->Xmin, inf->Xmax, inf->NbinsY, inf->Ymin, inf->Ymax);
}

InputTH1Info FillStruct(TString fName, TString fTitle, Int_t fNbins, Int_t fXmin, Int_t fXmax)
{
   InputTH1Info fInput;
   fInput.name = fName;
   fInput.title = fTitle;
   fInput.Nbins = fNbins;
   fInput.Xmin = fXmin;
   fInput.Xmax = fXmax;
   
   return fInput;
}

InputTH2Info FillStruct(TString fName, TString fTitle, Int_t fNbinsX, Int_t fXmin, Int_t fXmax, Int_t fNbinsY, Int_t fYmin, Int_t fYmax)
{
   InputTH2Info fInput;
   fInput.name = fName;
   fInput.title = fTitle;
   fInput.NbinsX = fNbinsX;
   fInput.Xmin = fXmin;
   fInput.Xmax = fXmax;
   fInput.NbinsX = fNbinsY;
   fInput.Xmin = fYmin;
   fInput.Xmax = fYmax;
   
   return fInput;
}

// Header file for the classes stored in the TTree if any.

class PicoDstPidReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   
   TH1F * h_mass2[Npid][NptBins][NetaBins];
   TH1F * h_PDG_mass2[Npid][NptBins][NetaBins];
   
   TH1F * h_bad_PDG[Npid][NptBins][NetaBins];
   
   BinningData* bins = new BinningData();

   // Declaration of leaf types
   Float_t         b_mc;
   Float_t         phiEP_mc;
   Float_t         x_vertex_mc;
   Float_t         y_vertex_mc;
   Float_t         z_vertex_mc;
   Float_t         x_vertex_mpd;
   Float_t         y_vertex_mpd;
   Float_t         z_vertex_mpd;
   Long64_t        n_tracks_mc;
   Float_t         eta_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         pt_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Int_t           mother_ID_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Int_t           PDG_code_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         px_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         py_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         pz_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         start_x_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         start_y_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         start_z_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         mass_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Float_t         energy_mc[_MAX_TRACKS];   //[n_tracks_mc]
   Long64_t        n_tracks_mpd;
   Long64_t        k_tracks_mpd;
   Float_t         eta_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         phi_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         theta_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Int_t           TOF_flag_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         ZDC_energy_mpd[90];
   Float_t         pid_tpc_prob_electron_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_pion_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_kaon_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tpc_prob_proton_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tof_prob_electron_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tof_prob_pion_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tof_prob_kaon_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pid_tof_prob_proton_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         tof_beta_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         tof_mass2_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         dEdx_tpc_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         chi2_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         chi2_vertex[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         pt_error_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         theta_error_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         phi_error_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         DCA_x_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         DCA_y_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         DCA_z_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Int_t           n_hits_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Int_t           n_hits_poss_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         signed_pt_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Int_t           centrality_tpc_mpd;
   Long64_t        id_from_mc_mpd[_MAX_TRACKS];   //[n_tracks_mpd]
   Float_t         p_mpd[_MAX_TRACKS];   //[n_tracks_mpd]

   // List of branches
   TBranch        *b_b_mc;   //!
   TBranch        *b_phiEP_mc;   //!
   TBranch        *b_x_vertex_mc;   //!
   TBranch        *b_y_vertex_mc;   //!
   TBranch        *b_z_vertex_mc;   //!
   TBranch        *b_x_vertex_mpd;   //!
   TBranch        *b_y_vertex_mpd;   //!
   TBranch        *b_z_vertex_mpd;   //!
   TBranch        *b_n_tracks_mc;   //!
   TBranch        *b_eta_mc;   //!
   TBranch        *b_pt_mc;   //!
   TBranch        *b_mother_ID_mc;   //!
   TBranch        *b_PDG_code_mc;   //!
   TBranch        *b_px_mc;   //!
   TBranch        *b_py_mc;   //!
   TBranch        *b_pz_mc;   //!
   TBranch        *b_start_x_mc;   //!
   TBranch        *b_start_y_mc;   //!
   TBranch        *b_start_z_mc;   //!
   TBranch        *b_mass_mc;   //!
   TBranch        *b_energy_mc;   //!
   TBranch        *b_n_tracks_mpd;   //!
   TBranch        *b_k_tracks_mpd;   //!
   TBranch        *b_eta_mpd;   //!
   TBranch        *b_phi_mpd;   //!
   TBranch        *b_theta_mpd;   //!
   TBranch        *b_TOF_flag_mpd;   //!
   TBranch        *b_ZDC_energy_mpd;   //!
   TBranch        *b_pid_tpc_prob_electron_mpd;   //!
   TBranch        *b_pid_tpc_prob_pion_mpd;   //!
   TBranch        *b_pid_tpc_prob_kaon_mpd;   //!
   TBranch        *b_pid_tpc_prob_proton_mpd;   //!
   TBranch        *b_pid_tof_prob_electron_mpd;   //!
   TBranch        *b_pid_tof_prob_pion_mpd;   //!
   TBranch        *b_pid_tof_prob_kaon_mpd;   //!
   TBranch        *b_pid_tof_prob_proton_mpd;   //!
   TBranch        *b_tof_beta_mpd;   //!
   TBranch        *b_tof_mass2_mpd;   //!
   TBranch        *b_dEdx_tpc_mpd;   //!
   TBranch        *b_chi2_mpd;   //!
   TBranch        *b_chi2_vertex;   //!
   TBranch        *b_pt_error_mpd;   //!
   TBranch        *b_theta_error_mpd;   //!
   TBranch        *b_phi_error_mpd;   //!
   TBranch        *b_DCA_x_mpd;   //!
   TBranch        *b_DCA_y_mpd;   //!
   TBranch        *b_DCA_z_mpd;   //!
   TBranch        *b_n_hits_mpd;   //!
   TBranch        *b_n_hits_poss_mpd;   //!
   TBranch        *b_signed_pt_mpd;   //!
   TBranch        *b_centrality_tpc_mpd;   //!
   TBranch        *b_id_from_mc_mpd;   //!
   TBranch        *b_p_mpd;   //!

   PicoDstPidReader(TTree *tree=0);
   PicoDstPidReader(TString inFileName);
   virtual ~PicoDstPidReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     InitAllHisto();
   virtual void     WriteAllHisto(TFile* inFile);
};

#endif

#ifdef PicoDstPidReader_cxx
PicoDstPidReader::PicoDstPidReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/peter/Documents/WorkLocal/MPD/RootFiles/merged_0_clone.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/merged_0_clone.root");
      }
      f->GetObject("cbmsim_reduced",tree);

   }
   Init(tree);
}

PicoDstPidReader::~PicoDstPidReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PicoDstPidReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PicoDstPidReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PicoDstPidReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("b_mc", &b_mc, &b_b_mc);
   fChain->SetBranchAddress("phiEP_mc", &phiEP_mc, &b_phiEP_mc);
   fChain->SetBranchAddress("x_vertex_mc", &x_vertex_mc, &b_x_vertex_mc);
   fChain->SetBranchAddress("y_vertex_mc", &y_vertex_mc, &b_y_vertex_mc);
   fChain->SetBranchAddress("z_vertex_mc", &z_vertex_mc, &b_z_vertex_mc);
   fChain->SetBranchAddress("x_vertex_mpd", &x_vertex_mpd, &b_x_vertex_mpd);
   fChain->SetBranchAddress("y_vertex_mpd", &y_vertex_mpd, &b_y_vertex_mpd);
   fChain->SetBranchAddress("z_vertex_mpd", &z_vertex_mpd, &b_z_vertex_mpd);
   fChain->SetBranchAddress("n_tracks_mc", &n_tracks_mc, &b_n_tracks_mc);
   fChain->SetBranchAddress("eta_mc", eta_mc, &b_eta_mc);
   fChain->SetBranchAddress("pt_mc", pt_mc, &b_pt_mc);
   fChain->SetBranchAddress("mother_ID_mc", mother_ID_mc, &b_mother_ID_mc);
   fChain->SetBranchAddress("PDG_code_mc", PDG_code_mc, &b_PDG_code_mc);
   fChain->SetBranchAddress("px_mc", px_mc, &b_px_mc);
   fChain->SetBranchAddress("py_mc", py_mc, &b_py_mc);
   fChain->SetBranchAddress("pz_mc", pz_mc, &b_pz_mc);
   fChain->SetBranchAddress("start_x_mc", start_x_mc, &b_start_x_mc);
   fChain->SetBranchAddress("start_y_mc", start_y_mc, &b_start_y_mc);
   fChain->SetBranchAddress("start_z_mc", start_z_mc, &b_start_z_mc);
   fChain->SetBranchAddress("mass_mc", mass_mc, &b_mass_mc);
   fChain->SetBranchAddress("energy_mc", energy_mc, &b_energy_mc);
   fChain->SetBranchAddress("n_tracks_mpd", &n_tracks_mpd, &b_n_tracks_mpd);
   fChain->SetBranchAddress("k_tracks_mpd", &k_tracks_mpd, &b_k_tracks_mpd);
   fChain->SetBranchAddress("eta_mpd", eta_mpd, &b_eta_mpd);
   fChain->SetBranchAddress("phi_mpd", phi_mpd, &b_phi_mpd);
   fChain->SetBranchAddress("theta_mpd", theta_mpd, &b_theta_mpd);
   fChain->SetBranchAddress("TOF_flag_mpd", TOF_flag_mpd, &b_TOF_flag_mpd);
   fChain->SetBranchAddress("ZDC_energy_mpd", ZDC_energy_mpd, &b_ZDC_energy_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_electron_mpd", pid_tpc_prob_electron_mpd, &b_pid_tpc_prob_electron_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_pion_mpd", pid_tpc_prob_pion_mpd, &b_pid_tpc_prob_pion_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_kaon_mpd", pid_tpc_prob_kaon_mpd, &b_pid_tpc_prob_kaon_mpd);
   fChain->SetBranchAddress("pid_tpc_prob_proton_mpd", pid_tpc_prob_proton_mpd, &b_pid_tpc_prob_proton_mpd);
   fChain->SetBranchAddress("pid_tof_prob_electron_mpd", pid_tof_prob_electron_mpd, &b_pid_tof_prob_electron_mpd);
   fChain->SetBranchAddress("pid_tof_prob_pion_mpd", pid_tof_prob_pion_mpd, &b_pid_tof_prob_pion_mpd);
   fChain->SetBranchAddress("pid_tof_prob_kaon_mpd", pid_tof_prob_kaon_mpd, &b_pid_tof_prob_kaon_mpd);
   fChain->SetBranchAddress("pid_tof_prob_proton_mpd", pid_tof_prob_proton_mpd, &b_pid_tof_prob_proton_mpd);
   fChain->SetBranchAddress("tof_beta_mpd", tof_beta_mpd, &b_tof_beta_mpd);
   fChain->SetBranchAddress("tof_mass2_mpd", tof_mass2_mpd, &b_tof_mass2_mpd);
   fChain->SetBranchAddress("dEdx_tpc_mpd", dEdx_tpc_mpd, &b_dEdx_tpc_mpd);
   fChain->SetBranchAddress("chi2_mpd", chi2_mpd, &b_chi2_mpd);
   fChain->SetBranchAddress("chi2_vertex", chi2_vertex, &b_chi2_vertex);
   fChain->SetBranchAddress("pt_error_mpd", pt_error_mpd, &b_pt_error_mpd);
   fChain->SetBranchAddress("theta_error_mpd", theta_error_mpd, &b_theta_error_mpd);
   fChain->SetBranchAddress("phi_error_mpd", phi_error_mpd, &b_phi_error_mpd);
   fChain->SetBranchAddress("DCA_x_mpd", DCA_x_mpd, &b_DCA_x_mpd);
   fChain->SetBranchAddress("DCA_y_mpd", DCA_y_mpd, &b_DCA_y_mpd);
   fChain->SetBranchAddress("DCA_z_mpd", DCA_z_mpd, &b_DCA_z_mpd);
   fChain->SetBranchAddress("n_hits_mpd", n_hits_mpd, &b_n_hits_mpd);
   fChain->SetBranchAddress("n_hits_poss_mpd", n_hits_poss_mpd, &b_n_hits_poss_mpd);
   fChain->SetBranchAddress("signed_pt_mpd", signed_pt_mpd, &b_signed_pt_mpd);
   fChain->SetBranchAddress("centrality_tpc_mpd", &centrality_tpc_mpd, &b_centrality_tpc_mpd);
   fChain->SetBranchAddress("id_from_mc_mpd", id_from_mc_mpd, &b_id_from_mc_mpd);
   fChain->SetBranchAddress("p_mpd", p_mpd, &b_p_mpd);
   Notify();
}

Bool_t PicoDstPidReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PicoDstPidReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PicoDstPidReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PicoDstPidReader_cxx
