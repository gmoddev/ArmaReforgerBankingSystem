// Not_Lowest
class TAG_BankingAction : ScriptedUserAction
{
    override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
    {
        EDF_JsonFileDbConnectionInfo connectInfo();
        connectInfo.m_sDatabaseName = "CapsDatabase";
        connectInfo.m_sFilePath = "Bank/Database/";

        EDF_DbContext dbContext = EDF_DbContext.Create(connectInfo);

        EDF_DbRepository<TAG_PlayerCaps> repository = EDF_DbEntityHelper<TAG_PlayerCaps>.GetRepository(dbContext);

        IEntity quantumCapsItem = pUserEntity.GetInventory().FindItemByName("QuantumCaps");
        if (quantumCapsItem)
        {
            TAG_PlayerCaps playerCaps = repository.FindFirstSync(pUserEntity.GetId());
            if (!playerCaps)
            {
                playerCaps = TAG_PlayerCaps.Create(0);
            }
            playerCaps.AddCaps(100);
            repository.AddOrUpdateAsync(playerCaps);

            pUserEntity.GetInventory().RemoveItem(quantumCapsItem);
            PrintFormat("100 caps added from Quantum Caps. New balance: %1", playerCaps.m_iCapsBalance);
        }

        IEntity capsX10Item = pUserEntity.GetInventory().FindItemByName("Caps_x10");
        if (capsX10Item)
        {
            TAG_PlayerCaps playerCaps = repository.FindFirstSync(pUserEntity.GetId());
            if (!playerCaps)
            {
                playerCaps = TAG_PlayerCaps.Create(0);
            }
            playerCaps.AddCaps(10);
            repository.AddOrUpdateAsync(playerCaps);

            pUserEntity.GetInventory().RemoveItem(capsX10Item);
            PrintFormat("10 caps added from Caps x10. New balance: %1", playerCaps.m_iCapsBalance);
        }

    }
};
