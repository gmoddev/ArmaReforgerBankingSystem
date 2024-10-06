// Not_Lowest
class WithdrawCapsUI : SCR_InfoDisplay
{
    private ButtonWidget m_WithdrawButton;
    private TextWidget m_CapsBalanceText;
    private TextEditWidget m_WithdrawAmountEdit;

    override event void OnStartDraw(IEntity owner)
    {
        super.OnStartDraw(owner);

        m_WithdrawButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("WithdrawButton"));
        m_CapsBalanceText = TextWidget.Cast(m_wRoot.FindAnyWidget("CapsBalanceText"));
        m_WithdrawAmountEdit = TextEditWidget.Cast(m_wRoot.FindAnyWidget("WithdrawAmountEdit"));

        m_WithdrawButton.AddHandler(WidgetEventType.BUTTON_CLICK, m_WithdrawButton.OnClick, this, "OnWithdrawButtonClicked");
    }

    void OnWithdrawButtonClicked()
    {
        int withdrawAmount = m_WithdrawAmountEdit.GetText().ToInt();
        TAG_PlayerCaps playerCaps = GetPlayerCaps();

        if (playerCaps && withdrawAmount > 0 && withdrawAmount <= playerCaps.m_iCapsBalance)
        {
            playerCaps.RemoveCaps(withdrawAmount);
            UpdateUI(playerCaps.m_iCapsBalance);
            AddCapsToInventory(owner, withdrawAmount);
        }
    }

    void UpdateUI(int currentBalance)
    {
        m_CapsBalanceText.SetText(currentBalance.ToString());
    }

    TAG_PlayerCaps GetPlayerCaps()
    {
        IEntity player = GetGame().GetPlayerController().GetControlledEntity();
        EDF_JsonFileDbConnectionInfo connectInfo();
        connectInfo.m_sDatabaseName = "CapsDatabase";
        connectInfo.m_sFilePath = "MyBankingMod/Database/";

        EDF_DbContext dbContext = EDF_DbContext.Create(connectInfo);
        EDF_DbRepository<TAG_PlayerCaps> repository = EDF_DbEntityHelper<TAG_PlayerCaps>.GetRepository(dbContext);

        return repository.FindFirstSync(player.GetId());
    }

    void AddCapsToInventory(IEntity player, int amount)
    {
        while (amount >= 100)
        {
            player.GetInventory().AddItem("QuantumCaps");
            amount -= 100;
        }

        while (amount >= 10)
        {
            player.GetInventory().AddItem("Caps_x10");
            amount -= 10;
        }
    }
}
