void runAnalysis()
{
    // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
    Bool_t local = kFALSE;//kTRUE;
    // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
    Bool_t gridTest = kFALSE;
    
    // since we will compile a class, tell root where to look for headers  
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/include");

    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
    AliAnalysisTask *pidtask = AddTaskPIDResponse(kFALSE,kTRUE);

    // compile the class (locally)
    gROOT->LoadMacro("AliAnalysisTaskMyTask.cxx++g");
    // load the addtask macro
    gROOT->LoadMacro("AddMyTask.C");
    // create an instance of your analysis task
    AliAnalysisTaskMyTask *task = AddMyTask();

    if(!mgr->InitAnalysis()) return;
    mgr->SetDebugLevel(2);
    mgr->PrintStatus();
    mgr->SetUseProgressBar(1, 25);

    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)
        //chain->Add("AliAODpp.root"); //pp
       // chain->Add("AliAODPbPb1.root");
       // chain->Add("AliAODPbPb2.root");
       // chain->Add("AliAODPbPb3.root");
       // chain->Add("AliAODPbPb4.root");
        /*chain->Add("AliAODMC01.root"); //MC
        chain->Add("AliAODMC02.root"); //MC
        chain->Add("AliAODMC03.root"); //MC
        chain->Add("AliAODMC04.root"); //MC
        chain->Add("AliAODMC05.root"); //MC   
        chain->Add("AliAODMC06.root"); //MC   
        chain->Add("AliAODMC07.root"); //MC   
        chain->Add("AliAODMC08.root"); //MC   
        chain->Add("AliAODMC09.root"); //MC   
        chain->Add("AliAODMC10.root"); //MC 
        chain->Add("AliAODMC11.root"); //MC 
        chain->Add("AliAODMC12.root"); //MC */
        //chain->Add("AliAODMC13.root"); //MC
        //chain->Add("AliAODMC14.root"); //MC
        chain->Add("AliAODMC2010_01.root"); //MC 2010
        chain->Add("AliAODMC2010_02.root"); //MC 2010
        chain->Add("AliAODMC2010_03.root"); //MC 2010
        chain->Add("AliAODMC2010_04.root"); //MC 2010
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskMyTask.cxx AliAnalysisTaskMyTask.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskMyTask.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20170806-1");
        // select the input data
       //alienHandler->SetGridDataDir("/alice/data/2015/LHC15f"); //pp
        //alienHandler->SetGridDataDir("/alice/data/2011/LHC11h_2");//PbPb
      // alienHandler->SetGridDataDir(" /alice/sim/2015/LHC15g3c3"); //MC
         alienHandler->SetGridDataDir(" /alice/sim/LHC10f6a"); // MC 2010
      //  alienHandler->SetDataPattern("pass2/AOD171/*AOD.root"); //pp
       // alienHandler->SetDataPattern("ESDs/pass2/AOD145/*AOD.root"); //PbPb
        //alienHandler->SetDataPattern("AOD/*AOD.root"); //MC
        alienHandler->SetDataPattern("AOD161/*AOD.root"); //MC 2010
        // MC has no prefix, data has prefix 000
        //alienHandler->SetRunPrefix("000");
        // runnumber
        //alienHandler->AddRunNumber(169858); //PbPb
        //alienHandler->AddRunNumber(169855); //PbPb
      /*  alienHandler->AddRunNumber(226500); //pp
        alienHandler->AddRunNumber(226495);
        alienHandler->AddRunNumber(226483);
        alienHandler->AddRunNumber(226476);
        alienHandler->AddRunNumber(226472);
        alienHandler->AddRunNumber(226468);
        alienHandler->AddRunNumber(226466);
        alienHandler->AddRunNumber(226452);
        alienHandler->AddRunNumber(226445);
        alienHandler->AddRunNumber(226444);
        alienHandler->AddRunNumber(226225);
        alienHandler->AddRunNumber(226220);
        alienHandler->AddRunNumber(226170);
        alienHandler->AddRunNumber(226062);
        alienHandler->AddRunNumber(225768);
        alienHandler->AddRunNumber(225766);
        alienHandler->AddRunNumber(225763);
        alienHandler->AddRunNumber(225762);
        alienHandler->AddRunNumber(225757);
        alienHandler->AddRunNumber(225753);
        alienHandler->AddRunNumber(225719);
        alienHandler->AddRunNumber(225717);
        alienHandler->AddRunNumber(225716);
        alienHandler->AddRunNumber(225710);
        alienHandler->AddRunNumber(225709);
        alienHandler->AddRunNumber(225708);
        alienHandler->AddRunNumber(225707);
        alienHandler->AddRunNumber(225705);
        alienHandler->AddRunNumber(225587);
        alienHandler->AddRunNumber(225586);
        alienHandler->AddRunNumber(225579);
        alienHandler->AddRunNumber(225578);
        alienHandler->AddRunNumber(225576);
        alienHandler->AddRunNumber(225322);
        alienHandler->AddRunNumber(225315);
        alienHandler->AddRunNumber(225314);
        alienHandler->AddRunNumber(225313);
        alienHandler->AddRunNumber(225310);
        alienHandler->AddRunNumber(225309);
        alienHandler->AddRunNumber(225307);
        alienHandler->AddRunNumber(225305);
        alienHandler->AddRunNumber(225106);
        alienHandler->AddRunNumber(225052);
        alienHandler->AddRunNumber(225051);
        alienHandler->AddRunNumber(225050);
        alienHandler->AddRunNumber(225043);
        alienHandler->AddRunNumber(225041);
        alienHandler->AddRunNumber(225037);
        alienHandler->AddRunNumber(225035);
        alienHandler->AddRunNumber(225031);
        alienHandler->AddRunNumber(225026);*/
        /*alienHandler->AddRunNumber(225768); //MC
        alienHandler->AddRunNumber(225587);
        alienHandler->AddRunNumber(226500);
        alienHandler->AddRunNumber(226495);
        alienHandler->AddRunNumber(226483);
        alienHandler->AddRunNumber(226476);
        alienHandler->AddRunNumber(226472);
        alienHandler->AddRunNumber(226468);
        alienHandler->AddRunNumber(226466);
        alienHandler->AddRunNumber(226452);
        alienHandler->AddRunNumber(226445);
        alienHandler->AddRunNumber(226444);
        alienHandler->AddRunNumber(226225);
        alienHandler->AddRunNumber(226220);
        alienHandler->AddRunNumber(226170);
        alienHandler->AddRunNumber(226062);
        alienHandler->AddRunNumber(225766);
        alienHandler->AddRunNumber(225763);
        alienHandler->AddRunNumber(225762);
        alienHandler->AddRunNumber(225757);
        alienHandler->AddRunNumber(225753);
        alienHandler->AddRunNumber(225719);
        alienHandler->AddRunNumber(225717);
        alienHandler->AddRunNumber(225716);
        alienHandler->AddRunNumber(225710);
        alienHandler->AddRunNumber(225709);
        alienHandler->AddRunNumber(225708);
        alienHandler->AddRunNumber(225707);
        alienHandler->AddRunNumber(225705);
        alienHandler->AddRunNumber(225587);
        alienHandler->AddRunNumber(225586);
        alienHandler->AddRunNumber(225579);
        alienHandler->AddRunNumber(225578);
        alienHandler->AddRunNumber(225576);
        alienHandler->AddRunNumber(225322);
        alienHandler->AddRunNumber(225315);
        alienHandler->AddRunNumber(225314);
        alienHandler->AddRunNumber(225313);
        alienHandler->AddRunNumber(225310);
        alienHandler->AddRunNumber(225309);
        alienHandler->AddRunNumber(225307);
        alienHandler->AddRunNumber(225305);
        alienHandler->AddRunNumber(225106);
        alienHandler->AddRunNumber(225052);
        alienHandler->AddRunNumber(225051);
        alienHandler->AddRunNumber(225050);
        alienHandler->AddRunNumber(225043);
        alienHandler->AddRunNumber(225041);
        alienHandler->AddRunNumber(225037);
        alienHandler->AddRunNumber(225035);
        alienHandler->AddRunNumber(225031);
        alienHandler->AddRunNumber(225026);*/
        alienHandler->AddRunNumber(122374); //MC2010
        alienHandler->AddRunNumber(122375);
        alienHandler->AddRunNumber(124751);
        alienHandler->AddRunNumber(125023);
        alienHandler->AddRunNumber(125085);
        alienHandler->AddRunNumber(125097);
        alienHandler->AddRunNumber(125100);
        alienHandler->AddRunNumber(125101);
        alienHandler->AddRunNumber(125133);
        alienHandler->AddRunNumber(125134);
        alienHandler->AddRunNumber(125139);
        alienHandler->AddRunNumber(125140);
        alienHandler->AddRunNumber(125156);
        alienHandler->AddRunNumber(125186);
        alienHandler->AddRunNumber(125296);
        alienHandler->AddRunNumber(125628);
        alienHandler->AddRunNumber(125630);
        alienHandler->AddRunNumber(125632);
        alienHandler->AddRunNumber(125633);
        alienHandler->AddRunNumber(125842);
        alienHandler->AddRunNumber(125843);
        alienHandler->AddRunNumber(125844);
        alienHandler->AddRunNumber(125847);
        alienHandler->AddRunNumber(125848);
        alienHandler->AddRunNumber(125849);
        alienHandler->AddRunNumber(125850);
        alienHandler->AddRunNumber(125851);
        alienHandler->AddRunNumber(125855);
        alienHandler->AddRunNumber(126004);
        alienHandler->AddRunNumber(126007);
        alienHandler->AddRunNumber(126073);
        alienHandler->AddRunNumber(126008);
        alienHandler->AddRunNumber(126078);
        alienHandler->AddRunNumber(126081);
        alienHandler->AddRunNumber(126082);
        alienHandler->AddRunNumber(126088);
        alienHandler->AddRunNumber(126090);
        alienHandler->AddRunNumber(126097);
        alienHandler->AddRunNumber(126158);
        alienHandler->AddRunNumber(126160);
        alienHandler->AddRunNumber(126167);
        alienHandler->AddRunNumber(126168);
        alienHandler->AddRunNumber(126283);
        alienHandler->AddRunNumber(126285);
        alienHandler->AddRunNumber(126284);
        alienHandler->AddRunNumber(126351);
        alienHandler->AddRunNumber(126350);
        alienHandler->AddRunNumber(126352);
        alienHandler->AddRunNumber(126359);
        alienHandler->AddRunNumber(126403);
        alienHandler->AddRunNumber(126404);
        alienHandler->AddRunNumber(126406);
        alienHandler->AddRunNumber(126405);
        alienHandler->AddRunNumber(126407);
        alienHandler->AddRunNumber(126408);
        alienHandler->AddRunNumber(126409);
        alienHandler->AddRunNumber(126422);
        alienHandler->AddRunNumber(126424);
        alienHandler->AddRunNumber(126425);
        alienHandler->AddRunNumber(126432);
        alienHandler->AddRunNumber(126437);
        
        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(40);
        alienHandler->SetExecutable("myTask.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("myTask.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with kTRUE to merge on grid
        // after re-running the jobs in SetRunMode("terminate") 
        // (see below) mode, set SetMergeViaJDL(kFALSE) 
        // to collect final results
        alienHandler->SetMaxMergeStages(1);
        alienHandler->SetMergeViaJDL(kFALSE);

        // define the output folders
        alienHandler->SetGridWorkingDir("myWorkingDirTestMC_32");
        alienHandler->SetGridOutputDir("myOutputDirTestMC_32");

        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis
            //alienHandler->SetRunMode("full"); //pocitanie
           alienHandler->SetRunMode("terminate"); //po vypocitani, iba na spojenie vysledkov
            mgr->StartAnalysis("grid");
        }
    }
} 
