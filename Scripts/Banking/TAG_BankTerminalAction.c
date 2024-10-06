// Not_Lowest
class TAG_BankTerminalAction : ScriptedUserAction
{
    override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
    {
        OpenWithdrawCapsUI(pUserEntity);
    }

    void OpenWithdrawCapsUI(IEntity pUserEntity)
    {
        WidgetManager widgetManager = GetGame().GetWidgetManager();
        LayoutRoot layoutRoot = widgetManager.LoadLayout("MyBankingMod/Layouts/WithdrawCaps.layout");

        WithdrawCapsUI uiScript = WithdrawCapsUI.Cast(layoutRoot.GetScript());
        TAG_PlayerCaps playerCaps = GetPlayerCaps(pUserEntity);

        if (uiScript && playerCaps)
        {
            uiScript.UpdateUI(playerCaps.m_iCapsBalance);
        }

        layoutRoot.Show(true);
    }

    TAG_PlayerCaps GetPlayerCaps(IEntity pUserEntity)
    {
        EDF_JsonFileDbConnectionInfo connectInfo();
        connectInfo.m_sDatabaseName = "CapsDatabase";
        connectInfo.m_sFilePath = "MyBankingMod/Database/";

        EDF_DbContext dbContext = EDF_DbContext.Create(connectInfo);
        EDF_DbRepository<TAG_PlayerCaps> repository = EDF_DbEntityHelper<TAG_PlayerCaps>.GetRepository(dbContext);

        return repository.FindFirstSync(pUserEntity.GetId());
    }
}
