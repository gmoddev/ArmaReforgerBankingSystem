// Not_Lowest + a little AI
class TAG_BankTerminal : Entity
{
    ref InventoryStorage m_Inventory;

    void TAG_BankTerminal()
    {
        m_Inventory = new InventoryStorage();
        m_Inventory.SetSize(10, 10);
    }

    void LoadCapsFromPlayer(TAG_PlayerCaps playerCaps)
    {
        m_Inventory.Clear();

        int remainingCaps = playerCaps.m_iCapsBalance;

        while (remainingCaps >= 100)
        {
            m_Inventory.AddItem("QuantumCaps");
            remainingCaps -= 100;
        }

        while (remainingCaps >= 10)
        {
            m_Inventory.AddItem("Caps_x10");
            remainingCaps -= 10;
        }
    }

    void SaveCapsToPlayer(TAG_PlayerCaps playerCaps)
    {
        int totalCaps = 0;

        array<IEntity> quantumCapsItems = {};
        m_Inventory.FindItemsByName("QuantumCaps", quantumCapsItems);
        totalCaps += quantumCapsItems.Count() * 100;

        array<IEntity> capsX10Items = {};
        m_Inventory.FindItemsByName("Caps_x10", capsX10Items);
        totalCaps += capsX10Items.Count() * 10;

        playerCaps.m_iCapsBalance = totalCaps;
    }
};